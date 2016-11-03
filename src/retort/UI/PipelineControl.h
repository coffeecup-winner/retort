#pragma once

#include <UI/Control.h>

namespace Retort::UI {
    class PipelineControl : public Control {

    public:
        Feedback consume(const SDL_Event &event) override;
        void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) override;
    };
}
