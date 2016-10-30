#pragma once

#include <memory>

#include <Graphics/Renderer.h>

using namespace Retort::Graphics;

namespace Retort::UI {
    class Control {
        Control(Control const &) = delete;
        Control &operator=(Control const &) = delete;

        Rect _bounds;
        Color _backgroundColor;

    protected:
        Control();
        const Rect getBounds();
        const Color getBackgroundColor();

    public:
        virtual void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) = 0;
        void move(int x, int y);
        void resize(int w, int h);
    };
}
