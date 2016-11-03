#include "SDLEnvironment.h"

namespace Retort::Graphics {
    SDLEnvironment::SDLEnvironment() {
        _isValid = false;
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            SDL_Quit();
            std::cout << "IMG_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        if (TTF_Init() != 0) {
            IMG_Quit();
            SDL_Quit();
            std::cout << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return;
        }
        _isValid = true;
    }

    SDLEnvironment::~SDLEnvironment() {
        if (_isValid) {
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
        }
    }

    bool SDLEnvironment::isValid() const {
        return _isValid;
    }
}
