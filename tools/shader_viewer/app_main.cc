#include <atomic>
#include <iostream>
#include <stdexcept>
#include <thread>

#include <gs/os/window.hh>
#include <gs/os/window_event.hh>

#include <gs/graphics/render_context.hh>
#include <gs/graphics/shader.hh>
#include <gs/graphics/shader_program.hh>
#include <gs/graphics/vertex_attribute.hh>
#include <gs/graphics/vertex_buffer.hh>

extern void watch(std::filesystem::path vsPath, std::filesystem::path fsPath);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "usage: " << argv[0]
                  << " <vertex_shader> <fragment_shader>" << std::endl;
        return EXIT_SUCCESS;
    }
    std::filesystem::path vsPath = argv[1];
    std::filesystem::path fsPath = argv[2];

    gs::os::Window window;
    window.open(640, 480, "hot-reloading shader viewer by addelajnen");

    gs::graphics::RenderContext renderer(window.getHandle());

    gs::graphics::Shader vs;
    vs.load(vsPath, gs::graphics::Shader::Type::Vertex);

    gs::graphics::Shader fs;
    fs.load(fsPath, gs::graphics::Shader::Type::Fragment);

    gs::graphics::ShaderProgram program;
    program.load(vs, fs);

    float vertices[3][7] = {
        {-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f},
        { 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f},
        { 0.0f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f}
    };

    gs::graphics::VertexBuffer vb(
        vertices, 3, sizeof(float) * 7, gs::graphics::FloatXYZRGBA);

    gs::math::Matrix4x4 transform(1.0f,
                                  0.0f,
                                  0.0f,
                                  0.0f,
                                  0.0f,
                                  1.0f,
                                  0.0f,
                                  0.0f,
                                  0.0f,
                                  0.0f,
                                  1.0f,
                                  0.0f,
                                  0.0f,
                                  0.0f,
                                  0.0f,
                                  1.0f);

    std::atomic_bool reload = false;
    std::thread      t([&]() {
        std::wcout << L"watching "
                   << (std::filesystem::current_path() /
                       std::filesystem::absolute(vsPath))
                          .remove_filename()
                          .c_str()
                   << std::endl;

        HANDLE hwatcher = FindFirstChangeNotificationW(
            (std::filesystem::current_path() /
             std::filesystem::absolute(vsPath))
                .remove_filename()
                .c_str(),
            FALSE,
            FILE_NOTIFY_CHANGE_LAST_WRITE);
        if (!hwatcher || hwatcher == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("failed to watch");
        }

        while (!window.isClosed()) {
            auto status = WaitForSingleObject(hwatcher, 5000);
            if (status == WAIT_OBJECT_0) {
                std::cout << "shader updated" << std::endl;
                reload = true;
                if (!FindNextChangeNotification(hwatcher)) {
                    throw std::runtime_error("watcher failed");
                }
            } else if (status != WAIT_TIMEOUT) {
                throw std::runtime_error("watcher failed");
            }
        }

        FindCloseChangeNotification(hwatcher);
    });

    while (!window.isClosed()) {
        auto event = window.pollEvents();
        if (event) {
            if (event->type == gs::os::WindowEvent::Type::Closed) {
                window.close();
            }
        }

        if (reload) {
            vs.release();
            fs.release();
            program.release();

            vs.load(vsPath, gs::graphics::Shader::Type::Vertex);
            fs.load(fsPath, gs::graphics::Shader::Type::Fragment);
            program.load(vs, fs);

            reload = false;
        } else {
            renderer.clear();
            program.use();
            program.setMatrix4("transform", transform.m);
            renderer.draw(vb, 0, 3, gs::graphics::Primitive::Triangles);
            renderer.swapBuffers();
        }
    }

    t.join();

    return EXIT_SUCCESS;
}
/*
#include <atomic>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <thread>
#include <mutex>

#include <windows.h>

#include <gs/os/window.hh>
#include <gs/os/window_event.hh>
#include <gs/graphics/render_context.hh>
#include <gs/graphics/shader.hh>
#include <gs/graphics/shader_program.hh>
#include <gs/graphics/vertex_buffer.hh>

class App {
public:
    App();
    ~App();

    void useProgram(const gs::math::Matrix4x4& transform);

    bool isQuitting();

private:
    void reloadShaders();

    static void watchShaders(App* app);

    std::thread reloadShadersThread;
    std::atomic_bool shouldQuit;
    std::atomic_bool shouldReload;
    gs::graphics::Shader vs;
    gs::graphics::Shader fs;
    gs::graphics::ShaderProgram program;
};

void App::reloadShaders() {
    if (shouldReload) {
        vs.load("assets/shaders/vertex_shader.glsl",
gs::graphics::Shader::Type::Vertex);
        fs.load("assets/shaders/fragment_shader.glsl",
gs::graphics::Shader::Type::Fragment); program.load(vs, fs);

        shouldReload = false;
    }
}

App::App() : shouldQuit(false), shouldReload(true),
reloadShadersThread(App::watchShaders, this) { reloadShaders();
}

App::~App() {
    shouldQuit = true;
    reloadShadersThread.join();
}

void App::useProgram(const gs::math::Matrix4x4& transform) {
    if (!shouldReload) {
        program.use();
        program.setMatrix4("transform", transform.m);
    }
}

bool App::isQuitting() {
    return shouldQuit;
}

void App::watchShaders(App* app) {
    HANDLE      hWatcher = nullptr;
    std::string err      = "";

    std::filesystem::path path(std::filesystem::current_path() /
                               TEXT("assets") / TEXT("shaders"));

    hWatcher = FindFirstChangeNotificationW(
        path.c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
    if (!hWatcher || hWatcher == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("failed to watch");
    }

    while (!app->isQuitting()) {
        try {
            auto status = WaitForSingleObject(hWatcher, 5000);
            if (status != WAIT_OBJECT_0 && status != WAIT_TIMEOUT) {
                throw std::runtime_error("watcher failed");
            }

            if (!FindNextChangeNotification(hWatcher)) {
                throw std::runtime_error(
                    "failed to get next watch notification");
            }

            if (status == WAIT_OBJECT_0) {
                app->shouldReload = true;
            }
        } catch (const std::exception& e) {
            err  = e.what();
            wchar_t message[256];
            MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, e.what(), -1, message,
256); MessageBox(nullptr, message, TEXT("Error"), MB_OK | MB_ICONERROR);

        }
    }

    if (hWatcher) {
        FindCloseChangeNotification(hWatcher);
        hWatcher = nullptr;
    }

    if (err.length() > 0) {
        throw std::runtime_error(err);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPWSTR    lpCmdLine,
                    int       nShowCmd) {
    try {
        gs::os::Window window;
        window.open(640, 480, "test");


        gs::graphics::RenderContext rc(window.getHandle());

        App app;

        float vertices[3][7] = {
            { -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
            {  0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f },
            {  0.0f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
        };

        gs::math::Matrix4x4 transform = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };

        transform.translate(0.25f, 0.25f, 0.0f);

        float angle = 0.0f;
        gs::graphics::VertexBuffer vb(vertices, 3, sizeof(float) * 7, {
            gs::graphics::VertexAttribute{
                .type = gs::graphics::VertexAttribute::Type::Float,
                .size = 3,
                .usage = gs::graphics::VertexAttribute::Usage::Position,
            },
            gs::graphics::VertexAttribute{
                .type = gs::graphics::VertexAttribute::Type::Float,
                .size = 4,
                .usage = gs::graphics::VertexAttribute::Usage::Color,
            }
        });

        while (!window.isClosed()) {
            auto event = window.pollEvents();
            if (event) {
                if (event->type == gs::os::WindowEvent::Type::Closed) {
                    window.close();
                } else if (event->type == gs::os::WindowEvent::Type::Resized) {
                    rc.updateViewport(0, 0, event->data.resized.width,
event->data.resized.height);
                }
            }
            rc.clear();
            app.useProgram(transform);
            rc.draw(vb, 0, 3, gs::graphics::Primitive::Triangles);
            rc.swapBuffers();
        }
    } catch (const std::exception& e) {
        wchar_t message[256];
        MultiByteToWideChar(CP_UTF8, MB_COMPOSITE, e.what(), -1, message, 256);
        MessageBox(nullptr, message, TEXT("Error"), MB_OK | MB_ICONERROR);
    }

    return EXIT_SUCCESS;
}
*/
