#pragma once
#include <common.h>

#include <SDL.h>

namespace Retort::Graphics {
    typedef SDL_Color Color;

    class Colors {
        noncopyable(Colors)

    public:
        static const Color WHITE;
        static const Color BLACK;
    };
}
