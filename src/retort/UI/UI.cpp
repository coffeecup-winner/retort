#include "UI.h"

namespace Retort::UI {
    UI::UI(std::shared_ptr<Renderer> renderer)
        : Transformer()
        , _fonts(std::make_shared<Fonts>())
        , _renderer(renderer)
        , _root(std::shared_ptr<Control>())
    { }

    void UI::show(std::shared_ptr<Control> control) {
        _root = control;
        _root->resize(640, 480); // TODO: merge with Window to remove the hard-coded values
        _root->setConsumer(_consumer);
    }

    Feedback UI::consume(const SDL_Event &event) {
        if (event.type == SDL_QUIT) {
            return Feedback::Stop;
        }
        return _root->consume(event);
    }

    Feedback UI::frameEnded() {
        auto feedback = _root->frameEnded();
        _root->render(_renderer, _fonts);
        _renderer->present();
        return feedback;
    }
}
