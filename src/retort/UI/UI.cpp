#include "UI.h"

namespace Retort::UI {
    UI::UI(std::shared_ptr<Renderer> renderer)
        : Consumer()
        , _fonts(std::make_shared<Fonts>())
        , _renderer(renderer)
        , _root(std::make_shared<PipelineControl>())
    {
        // TODO: merge with Window to remove the hard-coded values
        _root->resize(640, 480);
    }

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
        _root->render(_renderer, _fonts);
        _renderer->present();
        return Feedback::Continue;
    }
}
