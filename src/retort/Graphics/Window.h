#pragma once
#include <common.h>

#include <SDL.h>

namespace Retort::Graphics {
    class Window {
        NONCOPYABLE(Window)

        std::shared_ptr<SDL_Window> _window;

    public:
        Window(const std::string &str, int w, int h);
        SDL_Window *getSDLWindow();
    };
}
