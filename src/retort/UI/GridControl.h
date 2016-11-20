#pragma once
#include <common.h>

#include <Scripting/Reference.h>
#include <UI/Control.h>

using namespace Retort::Scripting;

namespace Retort::UI {
    class GridControl : public Control {
        NONCOPYABLE(GridControl)

        static const int CellSize = 32;

        int _offsetX = 0;
        int _offsetY = 0;
        bool _isDraggingViewport = false;
        std::shared_ptr<Reference> _control;

    public:
        GridControl(const std::string &name, std::shared_ptr<Reference> &control);
        Feedback consume(const SDL_Event &event) override;
        void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> &fonts, std::shared_ptr<Sprites> &sprites) override;
    };
}
