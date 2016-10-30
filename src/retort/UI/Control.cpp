#include "Control.h"

namespace Retort::UI {
    Control::Control()
        : _bounds({ 0, 0, 0, 0 })
        , _backgroundColor(Colors::WHITE)
    { }

    const Rect Control::getBounds() {
        return _bounds;
    }

    const Color Control::getBackgroundColor() {
        return _backgroundColor;
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
