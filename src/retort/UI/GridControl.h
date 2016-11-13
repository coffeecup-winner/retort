#pragma once
#include <common.h>

#include <UI/Control.h>

namespace Retort::UI {
    class GridControl : public Control {
        noncopyable(GridControl)

    public:
        explicit GridControl(const std::string &name);
        Feedback consume(const SDL_Event &event) override;
        void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) override;
    };
}
