#include "UI.h"

namespace Retort::UI {
    UI::UI(std::shared_ptr<Renderer> renderer)
        : Transformer()
        , _scriptObject(std::make_shared<UIScriptObject>())
        , _fonts(std::make_shared<Fonts>())
        , _renderer(renderer)
        , _root(std::make_shared<GridControl>("pipeline"))
        , _controls(std::map<std::string, std::weak_ptr<Control>>())
    {
        // TODO: merge with Window to remove the hard-coded values
        _root->resize(640, 480);
        _controls.insert(std::make_pair(_root->getName(), _root));
    }

    void UI::setConsumer(std::shared_ptr<Consumer<UIEvent>> consumer) {
        _root->setConsumer(consumer);
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

    std::shared_ptr<UIScriptObject> UI::getScriptObject() const {
        return _scriptObject;
    }
}
