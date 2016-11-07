#pragma once

#include <memory>
#include <map>

#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Renderer.h>
#include <Scripting/UIScriptObject.h>
#include <UI/UIEvent.h>
#include <UI/GridControl.h>
#include <Utilities/Transformer.h>

using namespace Retort::Graphics;
using namespace Retort::Scripting;
using namespace Retort::Utilities;

namespace Retort::UI {
    class UI : public Transformer<SDL_Event, UIEvent> {
        UI(UI const &) = delete;
        UI &operator=(UI const &) = delete;

        std::shared_ptr<Fonts> _fonts;
        std::shared_ptr<Renderer> _renderer;

        std::shared_ptr<UIScriptObject> _scriptObject;
        std::shared_ptr<GridControl> _root;
        std::map<std::string, std::weak_ptr<Control>> _controls;

    public:
        explicit UI(std::shared_ptr<Renderer> renderer);
        void setConsumer(std::shared_ptr<Consumer<UIEvent>> consumer) override;
        Feedback consume(const SDL_Event &event) override;
        Feedback frameEnded() override;

        std::shared_ptr<UIScriptObject> getScriptObject() const;
    };
}
