#pragma once
#include <common.h>

#include <UI/Control.h>

namespace Retort::UI {
    class Panel : public Control {
        NONCOPYABLE(Panel)

    public:
        explicit Panel(const std::string &name);
        void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> &fonts, std::shared_ptr<Sprites> &sprites) override;
    };
}
