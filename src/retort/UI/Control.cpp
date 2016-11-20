#include "Control.h"

namespace Retort::UI {
    Control::Control(const std::string &name)
        : Transformer()
        , _name(name)
    { }

    int Control::getMouseDownX() const {
        return _mouseDownX;
    }

    int Control::getMouseDownY() const {
        return _mouseDownY;
    }

    Control::~Control() { }

    const std::string &Control::getName() const {
        return _name;
    }

    const Rect &Control::getBounds() const {
        return _bounds;
    }

    const Color &Control::getBackgroundColor() const {
        return _backgroundColor;
    }

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
