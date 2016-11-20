#include "SDLEnvironment.h"

namespace Retort::Graphics {
    SDLEnvironment::SDLEnvironment() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			CRASH("Failed to initialize SDL: %s", SDL_GetError());
            return;
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			CRASH("Failed to initialize SDL_IMG: %s", SDL_GetError());
            SDL_Quit();
            return;
        }

        if (TTF_Init() != 0) {
			CRASH("Failed to initialize SDL_TTF: %s", SDL_GetError());
            IMG_Quit();
            SDL_Quit();
            return;
        }
    }

	SDLEnvironment::~SDLEnvironment() {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
}
