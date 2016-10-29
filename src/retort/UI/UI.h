#pragma once

#include <memory>

#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Renderer.h>
#include <Utilities/Consumer.h>

using namespace Retort::Graphics;
using namespace Retort::Utilities;

namespace Retort::UI {
    class UI : public Consumer<SDL_Event> {
        UI(UI const &) = delete;
        UI &operator=(UI const &) = delete;

        std::shared_ptr<Fonts> _fonts;
        std::shared_ptr<Renderer> _renderer;

    public:
        explicit UI(std::shared_ptr<Renderer> renderer);
        Feedback consume(SDL_Event) override;
        Feedback frameEnded() override;
    };
}
