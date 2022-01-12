#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include <windows.h>

#include <gs/os/file_watcher.hh>

extern std::wstring GetLastErrorAsString();

namespace gs {
namespace os {
struct FileWatcher::Implementation {
    Implementation();
    ~Implementation();

    void shutdown();
    void runWatcher();

    static const unsigned int MAX_FILE_NOTIFY_BUFFER_SIZE = 4096;

    struct Handler {
        std::filesystem::path                         path;
        HandlerFunc                                   handlerFunc;
        OVERLAPPED                                    overlapped;
        HANDLE                                        hFile;
        HANDLE                                        hCompletionPort;
        std::array<BYTE, MAX_FILE_NOTIFY_BUFFER_SIZE> bytes;
    };

    HANDLE      hRootCompletionPort;
    std::thread thread;
    std::unordered_map<LPOVERLAPPED, std::unique_ptr<Handler>> handlers;
};

FileWatcher::Implementation::Implementation()
    : hRootCompletionPort(
          ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) {
    if (hRootCompletionPort == INVALID_HANDLE_VALUE || !hRootCompletionPort) {
        throw std::runtime_error("failed to create io completion port");
    }
}

FileWatcher::Implementation::~Implementation() {
    shutdown();
}

void FileWatcher::Implementation::shutdown() {
    for (auto it = handlers.begin(); it != handlers.end(); it++) {
        if (it->second->hFile) {
            ::CloseHandle(it->second->hFile);
            it->second->hFile = nullptr;
        }

        if (it->second->hCompletionPort) {
            ::CloseHandle(it->second->hCompletionPort);
            it->second->hCompletionPort = nullptr;
        }
    }

    if (hRootCompletionPort) {
        ::CloseHandle(hRootCompletionPort);
        hRootCompletionPort = nullptr;
    }
}

void FileWatcher::Implementation::runWatcher() {
    if (handlers.size() > 0 && !thread.joinable()) {
        if (hRootCompletionPort == INVALID_HANDLE_VALUE ||
            !hRootCompletionPort) {
            throw std::runtime_error("invalid handle value");
        }

        thread = std::thread([&] {
            while (hRootCompletionPort) {
                DWORD        queuedByteCount     = 0;
                ULONG_PTR    queuedCompletionKey = 0;
                LPOVERLAPPED queuedOverlapped    = nullptr;

                if (!GetQueuedCompletionStatus(hRootCompletionPort,
                                               &queuedByteCount,
                                               &queuedCompletionKey,
                                               &queuedOverlapped,
                                               INFINITE)) {
                    if (!queuedOverlapped &&
                        GetLastError() == ERROR_ABANDONED_WAIT_0) {
                        break;
                    } else {
                        throw std::runtime_error(
                            "failed to wait for completion status");
                    }
                }

                if (queuedByteCount == 0) {
                    break;
                }

                auto it = handlers.find(queuedOverlapped);
                if (it != handlers.end()) {
                    auto& handler = *it->second;

                    FILE_NOTIFY_INFORMATION* fni =
                        reinterpret_cast<decltype(fni)>(handler.bytes.data());
                    for (;;) {
                        FileWatcher::FileAction action =
                            FileWatcher::FileAction::Unknown;
                        switch (fni->Action) {
                        case FILE_ACTION_ADDED:
                            action = FileWatcher::FileAction::Added;
                            break;
                        case FILE_ACTION_REMOVED:
                            action = FileWatcher::FileAction::Removed;
                            break;
                        case FILE_ACTION_MODIFIED:
                            action = FileWatcher::FileAction::Modified;
                            break;
                        case FILE_ACTION_RENAMED_OLD_NAME:
                            action = FileWatcher::FileAction::RenamedFrom;
                            break;
                        case FILE_ACTION_RENAMED_NEW_NAME:
                            action = FileWatcher::FileAction::RenamedTo;
                            break;
                        }

                        std::wstring filename(fni->FileName,
                                              fni->FileNameLength /
                                                  sizeof(wchar_t));

                        handler.handlerFunc(action, handler.path / filename);

                        if (!fni->NextEntryOffset) {
                            break;
                        }

                        fni = reinterpret_cast<decltype(fni)>(
                            fni->NextEntryOffset +
                            reinterpret_cast<uintptr_t>(fni));
                    }

                    if (handler.hFile && hRootCompletionPort) {
                        if (!ReadDirectoryChangesW(
                                handler.hFile,
                                handler.bytes.data(),
                                handler.bytes.size(),
                                TRUE,
                                FILE_NOTIFY_CHANGE_LAST_WRITE |
                                    FILE_NOTIFY_CHANGE_FILE_NAME |
                                    FILE_NOTIFY_CHANGE_DIR_NAME,
                                NULL,
                                &handler.overlapped,
                                NULL)) {
                            throw std::runtime_error(
                                "failed to re-watch directory");
                        }
                    }
                }
            }
        });
    }
}

FileWatcher::FileWatcher()
    : implementation(std::make_unique<Implementation>()) {
}

FileWatcher::~FileWatcher() {
    implementation->shutdown();
    if (implementation->thread.joinable()) {
        implementation->thread.join();
    }
}

void FileWatcher::watch(const std::filesystem::path& path,
                        FileWatcher::HandlerFunc     handlerFunc) {
    auto hFile = CreateFileW(path.c_str(),
                             FILE_LIST_DIRECTORY | GENERIC_READ | GENERIC_WRITE,
                             FILE_SHARE_READ | FILE_SHARE_WRITE |
                                 FILE_SHARE_DELETE,
                             NULL,
                             OPEN_EXISTING,
                             FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
                             NULL);
    if (hFile == INVALID_HANDLE_VALUE || !hFile) {
        throw std::runtime_error("failed to open directory");
    }
    auto hCompletionPort = CreateIoCompletionPort(
        hFile, implementation->hRootCompletionPort, 0, 0);
    if (hCompletionPort == INVALID_HANDLE_VALUE || !hCompletionPort) {
        throw std::runtime_error("failed to create io port for directory");
    }

    auto handler = std::make_unique<FileWatcher::Implementation::Handler>(
        FileWatcher::Implementation::Handler{
            .path            = path,
            .handlerFunc     = handlerFunc,
            .overlapped      = OVERLAPPED{0},
            .hFile           = hFile,
            .hCompletionPort = hCompletionPort,
        });

    if (!ReadDirectoryChangesW(hFile,
                               handler->bytes.data(),
                               handler->bytes.size(),
                               TRUE,
                               FILE_NOTIFY_CHANGE_LAST_WRITE |
                                   FILE_NOTIFY_CHANGE_FILE_NAME |
                                   FILE_NOTIFY_CHANGE_DIR_NAME,
                               0,
                               &handler->overlapped,
                               NULL)) {
        throw std::runtime_error("failed to watch directory");
    }

    implementation->handlers[&handler->overlapped] = std::move(handler);

    implementation->runWatcher();
}
} // namespace os
} // namespace gs