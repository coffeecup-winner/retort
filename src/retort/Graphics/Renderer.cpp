#include "Renderer.h"

namespace Retort::Graphics {
    Renderer::Renderer(Window &window)
        : _renderer(std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window.getSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer))
    { }

    bool Renderer::isValid() {
        return _renderer.get() != nullptr;
    }

    void Renderer::clear(Color color) {
        SDL_SetRenderDrawColor(_renderer.get(), color.r, color.g, color.b, color.a);
        SDL_RenderClear(_renderer.get());
    }

    void Renderer::present() {
        SDL_RenderPresent(_renderer.get());
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
