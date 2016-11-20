#pragma once
#include <common.h>

#include <SDL.h>
#include <SDL_image.h>

namespace Retort::Graphics {
    class Sprite {
        NONCOPYABLE(Sprite)

        std::string _name;
        SDL_Surface *_surface;

    public:
        explicit Sprite(const std::string &filepath);
        ~Sprite();
        const std::string &getName() const;
        SDL_Surface *get() const;
    };
}
