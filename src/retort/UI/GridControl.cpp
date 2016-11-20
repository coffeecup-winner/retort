#include "GridControl.h"

namespace Retort::UI {
    GridControl::GridControl(const std::string &name, std::shared_ptr<Reference> &control)
        : Control(name)
        , _control(control)
    { }

    Feedback GridControl::consume(const SDL_Event &event) {
        Control::consume(event);
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            int cellX = (getMouseDownX() - _offsetX - BorderWidth / 2) / (CellSize + BorderWidth);
            if (getMouseDownX() - _offsetX < 0) {
                --cellX;
            }
            int cellY = (getMouseDownY() - _offsetY - BorderWidth / 2) / (CellSize + BorderWidth);
            if (getMouseDownY() - _offsetY < 0) {
                --cellY;
            }
            auto click = UIEvent(getName(), GridControlEvent(cellX, cellY));
            _consumer->consume(click);
        }
        if (event.button.button == SDL_BUTTON_MIDDLE) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                _isDraggingViewport = true;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                _isDraggingViewport = false;
            }
        }
        if (event.type == SDL_MOUSEMOTION && _isDraggingViewport) {
            _offsetX += event.motion.xrel;
            _offsetY += event.motion.yrel;
        }
        return Feedback::Continue;
    }

    void GridControl::render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> &fonts, std::shared_ptr<Sprites> &sprites) {
        renderer->fillRect(getBackgroundColor(), getBounds());
        auto bounds = getBounds();
        const int left = bounds.x + _offsetX;
        const int top = bounds.y + _offsetY;
        
        const int gridLeft = left % (CellSize + BorderWidth) - (CellSize + BorderWidth);
        const int gridTop = top % (CellSize + BorderWidth) - (CellSize + BorderWidth);
        const int gridWidth = bounds.w + (CellSize + BorderWidth) * 2;
        const int gridHeight = bounds.h + (CellSize + BorderWidth) * 2;
        for (int dx = gridLeft; dx < gridWidth; dx += CellSize + BorderWidth) {
            renderer->drawLine(Colors::BLACK, dx + BorderWidth / 2, gridTop, dx + BorderWidth / 2, gridTop + gridHeight);
        }
        for (int dy = gridTop; dy < gridHeight; dy += CellSize + BorderWidth) {
            renderer->drawLine(Colors::BLACK, gridLeft, dy + BorderWidth / 2, gridLeft + gridWidth, dy + BorderWidth / 2);
        }
        auto control = _control->view();
        auto data = control->getTable("data");
        auto field = data->getTable("field");
        if (!field) return;
        
        const int cellLeft = -_offsetX / (CellSize + BorderWidth);
        const int cellTop = -_offsetY / (CellSize + BorderWidth);
        const int cellRight = cellLeft + bounds.w / (CellSize + BorderWidth) + 2;
        const int cellBottom = cellTop + bounds.h / (CellSize + BorderWidth) + 2;
        for (int x = cellLeft; x < cellRight; ++x) {
            auto column = field->getTable(x);
            if (!column) continue;
            for (int y = cellTop; y < cellBottom; ++y) {
                auto cell = column->getTable(y);
                if (!cell) continue;
                auto name = cell->getString("name");
                int i = 0, j = 0;
                if (name == "start") {
                    i = 1;
                } else if (name == "end") {
                    j = 1;
                }
                renderer->renderSprite(sprites->get("sprite0"), i, j, left + x * (CellSize + BorderWidth) + BorderWidth, top + y * (CellSize + BorderWidth) + BorderWidth);
            }
        }
    }
}
