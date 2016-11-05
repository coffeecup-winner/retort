#include "Control.h"

namespace Retort::UI {
    Control::Control()
        : Transformer()
        , _bounds({ 0, 0, 0, 0 })
        , _backgroundColor(Colors::WHITE)
    { }

    const Rect Control::getBounds() {
        return _bounds;
    }

    const Color Control::getBackgroundColor() {
        return _backgroundColor;
    }

    int Control::getMouseDownX() const {
        return _mouseDownX;
    }

    int Control::getMouseDownY() const {
        return _mouseDownY;
    }

    Control::~Control() { }

    Feedback Control::consume(const SDL_Event &event) {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            _mouseDownX = event.button.x;
            _mouseDownY = event.button.y;
        }
        return Feedback::Continue;
    }

    void Control::move(int x, int y) {
        _bounds.x = x;
        _bounds.y = y;
    }

    void Control::resize(int w, int h) {
        _bounds.w = w;
        _bounds.h = h;
    }
}
