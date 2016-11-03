#pragma once

#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Geometry.h>
#include <Graphics/Window.h>

namespace Retort::Graphics {
    class Renderer {
        Renderer(Renderer const &) = delete;
        Renderer &operator=(Renderer const &) = delete;

        std::shared_ptr<SDL_Renderer> _renderer;

    public:
        explicit Renderer(Window &window);
        bool isValid() const;

        void clear(Color color);
        void present();
        void drawLine(Color color, int x1, int y1, int x2, int y2);
        void fillRect(Color color, Rect rect);
        void renderText(std::shared_ptr<Font> font, Color color, std::string str, int x, int y);
    };
}
