#pragma once

#include <memory>
#include <string>

#include <SDL.h>

namespace Retort::Graphics {
    class Window {
        Window(Window const &) = delete;
        Window &operator=(Window const &) = delete;

        std::shared_ptr<SDL_Window> _window;

    public:
        Window(std::string str, int w, int h);
        bool isValid();
        SDL_Window *getSDLWindow();
    };
}