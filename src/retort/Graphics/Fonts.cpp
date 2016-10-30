#include "Fonts.h"

namespace Retort::Graphics {
    Fonts::Fonts()
        : _ubuntu14(std::shared_ptr<Font>(TTF_OpenFont("fonts/Ubuntu-R.ttf", 14), TTF_CloseFont))
    { }

    bool Fonts::isValid() {
        return _ubuntu14.get() != nullptr;
    }

    const std::shared_ptr<Font> Fonts::ubuntu14() {
        return _ubuntu14;
    }
}
