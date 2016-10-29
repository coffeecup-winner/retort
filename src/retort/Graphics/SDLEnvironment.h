#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

namespace Retort::Graphics {
    class SDLEnvironment {
        SDLEnvironment(const SDLEnvironment &) = delete;
        SDLEnvironment &operator=(const SDLEnvironment &) = delete;

        bool _isValid;

    public:
        SDLEnvironment();
        ~SDLEnvironment();
        bool isValid();
    };
}
