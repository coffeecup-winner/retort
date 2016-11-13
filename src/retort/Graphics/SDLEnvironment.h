#pragma once
#include <common.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Retort::Graphics {
    class SDLEnvironment {
        noncopyable(SDLEnvironment)

        bool _isValid;

    public:
        SDLEnvironment();
        ~SDLEnvironment();
        bool isValid() const;
    };
}
