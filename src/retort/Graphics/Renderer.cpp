#include "Renderer.h"

namespace Retort::Graphics {
    Renderer::Renderer(Window &window)
        : _renderer(std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer))
    {
		if (_renderer.get() == nullptr) {
			CRASH("Failed to create renderer: %s", SDL_GetError());
		}
	}

    void Renderer::clear(Color color) {
        SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
        SDL_RenderClear(_renderer.get());
    }

    void Renderer::present() {
        SDL_RenderPresent(_renderer.get());
    }

    void Renderer::drawLine(Color color, int x1, int y1, int x2, int y2) {
        SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(_renderer.get(), x1, y1, x2, y2);
    }

    void Renderer::fillRect(Color color, Rect rect) {
        SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(_renderer.get(), &rect);
    }

    void Renderer::renderText(std::shared_ptr<Font> font, Color color, std::string str, int x, int y) {
        auto surface = TTF_RenderText_Blended(font.get(), str.c_str(), color);
        auto texture = SDL_CreateTextureFromSurface(_renderer.get(), surface);
        SDL_Rect rect = { x, y, surface->w, surface->h };
        SDL_FreeSurface(surface);
        SDL_RenderCopy(_renderer.get(), texture, &surface->clip_rect, &rect);
        SDL_DestroyTexture(texture);
    }
}
