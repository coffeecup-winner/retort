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

    Feedback Control::consume(SDL_Event event) {
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
