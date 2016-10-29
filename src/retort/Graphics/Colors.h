#pragma once

#include <SDL.h>

namespace Retort::Graphics {
    class Colors {
        Colors(const Colors &) = delete;
        Colors &operator=(const Colors &) = delete;

    public:
        static const SDL_Color WHITE;
        static const SDL_Color BLACK;
    };
}
