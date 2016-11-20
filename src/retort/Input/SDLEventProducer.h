#pragma once
#include <common.h>

#include <SDL.h>

#include <Utilities/Consumer.h>
#include <Utilities/Producer.h>

using namespace Retort::Utilities;

namespace Retort::Input {

    class SDLEventProducer : public Producer<SDL_Event> {
        NONCOPYABLE(SDLEventProducer)

        SDL_Event _event;
    
    public:
        SDLEventProducer() = default;
        void run();
    };
}
