#include "SDLEventProducer.h"

namespace Retort::Input {
    void SDLEventProducer::run() {
		SDL_Event _event = {};
        do {
            while (SDL_PollEvent(&_event)) {
                if (_consumer->consume(_event) == Feedback::Stop) {
                    return;
                }
            }
        } while (_consumer->frameEnded() != Feedback::Stop);
    }
}
