#pragma once

#include <SDL.h>

#include <Utilities/Consumer.h>
#include <Utilities/Producer.h>

using namespace Retort::Utilities;

namespace Retort::Input {

    class SDLEventProducer : public Producer<SDL_Event> {
        SDLEventProducer(SDLEventProducer const &) = delete;
        SDLEventProducer &operator=(SDLEventProducer const &) = delete;

        SDL_Event _event;
    
    public:
        SDLEventProducer();
        void run();
    };
}
