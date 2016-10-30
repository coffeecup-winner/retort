#pragma once

#include <SDL.h>

namespace Retort::Graphics {
    typedef SDL_Color Color;

    class Colors {
        Colors(const Colors &) = delete;
        Colors &operator=(const Colors &) = delete;

    public:
        static const Color WHITE;
        static const Color BLACK;
    };
}
