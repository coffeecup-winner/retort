#pragma once
#include <common.h>

#include <Scripting/Reference.h>
#include <UI/Control.h>

using namespace Retort::Scripting;

namespace Retort::UI {
    class GridControl : public Control {
        NONCOPYABLE(GridControl)

        std::shared_ptr<Reference> _data;

    public:
        GridControl(const std::string &name, std::shared_ptr<Reference> data);
        Feedback consume(const SDL_Event &event) override;
        void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) override;
    };
}
