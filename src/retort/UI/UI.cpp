#include "UI.h"

namespace Retort::UI {
    UI::UI(std::shared_ptr<Renderer> renderer)
        : Consumer()
        , _fonts(std::make_shared<Fonts>())
        , _renderer(renderer)
    { }

    Feedback UI::consume(SDL_Event event) {
        if (event.type == SDL_QUIT) {
            return Feedback::Stop;
        }
        else if (event.type == SDL_KEYDOWN) {
            return Feedback::Stop;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            return Feedback::Stop;
        }
        return Feedback::Continue;
    }

    Feedback UI::frameEnded() {
        _renderer->clear(Colors::WHITE);
        _renderer->renderText(_fonts->ubuntu14(), Colors::BLACK, "Hello, world!", 10, 10);
        _renderer->present();
        return Feedback::Continue;
    }
}
