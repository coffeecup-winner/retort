#pragma once

#include <UI/Control.h>

namespace Retort::UI {
    class Panel : public Control {

    public:
        void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) override;
    };
}
