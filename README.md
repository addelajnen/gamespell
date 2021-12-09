# Gamespell

## About
My attempt to invent the wheel again by creating yet another graphics/game library from scratch instead of using the really good ones already out there...

**THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND**

## File structure

- assets/ misc assets like shaders/images etc.
- examples/ example projects to play around with.
- include/ all PUBLIC library headers.
- src/ all PRIVATE library source/headers.
    - src/libgamespell_core/ Gamespell core functionality like window creation, math etc (required)
    - src/libgamespell_main/ A cross platform solution for main, wmain, WinMain, wWinMain (optional)
    - src/libgamespell_opengl/ OpenGL 3.3+ renderer.
- tests/ misc tests
- tools/ misc tools to make life a little bit easier
- vcpkg/ optional submodule of vcpkg for dependencies
