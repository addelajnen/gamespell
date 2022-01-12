#ifndef GAMESPELL_OS_FILE_WATCHER_HH
#define GAMESPELL_OS_FILE_WATCHER_HH

#include <filesystem>
#include <functional>
#include <memory>

#include <gs/noncopyable.hh>
#include <gs/propagate_const.hh>

namespace gs {
namespace os {
class FileWatcher : private gs::Noncopyable {
public:
    enum class FileAction {
        Unknown = 0,
        Added,
        Removed,
        Modified,
        RenamedFrom,
        RenamedTo
    };

    using HandlerFunc = std::function<void(FileAction                   action,
                                           const std::filesystem::path& path)>;

    FileWatcher();
    ~FileWatcher();

    void watch(const std::filesystem::path& path, HandlerFunc handlerFunc);

private:
    struct Implementation;

    gs::PropagateConst<std::unique_ptr<Implementation>> implementation;
};
} // namespace os
} // namespace gs

#endif // GAMESPELL_OS_FILE_WATCHER_HH
