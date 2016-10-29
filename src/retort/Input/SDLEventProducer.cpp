#include "SDLEventProducer.h"

namespace Retort::Input {
    SDLEventProducer::SDLEventProducer() { }

    void SDLEventProducer::run() {
        do {
            while (SDL_PollEvent(&_event)) {
                if (_consumer->consume(_event) == Feedback::Stop) {
                    return;
                }
            }
        } while (_consumer->frameEnded() != Feedback::Stop);
    }
}
