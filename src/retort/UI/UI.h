#pragma once
#include <common.h>

#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Renderer.h>
#include <UI/UIEvent.h>
#include <UI/GridControl.h>
#include <Utilities/Transformer.h>

using namespace Retort::Graphics;
using namespace Retort::Utilities;

namespace Retort::UI {
    class UI : public Transformer<SDL_Event, UIEvent> {
        noncopyable(UI)

        std::shared_ptr<Fonts> _fonts;
        std::shared_ptr<Renderer> _renderer;

        std::shared_ptr<Control> _root;

    public:
        explicit UI(std::shared_ptr<Renderer> renderer);
        void show(std::shared_ptr<Control> control);
        Feedback consume(const SDL_Event &event) override;
        Feedback frameEnded() override;
    };
}
