#pragma once

#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Window.h"

namespace Retort::Graphics {
    class Renderer {
        Renderer(Renderer const &) = delete;
        Renderer &operator=(Renderer const &) = delete;

        std::shared_ptr<SDL_Renderer> _renderer;

    public:
        explicit Renderer(Window &window);
        bool isValid();

        void clear(SDL_Color color);
        void present();
        void renderText(std::shared_ptr<TTF_Font> font, SDL_Color color, std::string str, int x, int y);
    };
}
