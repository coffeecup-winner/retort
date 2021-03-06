#include "Window.h"

namespace Retort::Graphics {
    Window::Window(const std::string &str, int w, int h)
        : _window(std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(str.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN),
            SDL_DestroyWindow))
    {
		if (_window.get() == nullptr) {
			CRASH("Failed to create window: %s", SDL_GetError());
		}
	}

    SDL_Window* Window::getSDLWindow() {
        return _window.get();
    }
}
