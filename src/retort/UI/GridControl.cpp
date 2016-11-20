#include "GridControl.h"

namespace Retort::UI {
    GridControl::GridControl(const std::string &name, std::shared_ptr<Reference> &control)
        : Control(name)
        , _control(control)
    { }

    Feedback GridControl::consume(const SDL_Event &event) {
        Control::consume(event);
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            int cellX = (getMouseDownX() - _offsetX) / (CellSize + 1);
            if (getMouseDownX() - _offsetX < 0) {
                --cellX;
            }
            int cellY = (getMouseDownY() - _offsetY) / (CellSize + 1);
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
        
        const int gridLeft = left % (CellSize + 1) - (CellSize + 1);
        const int gridTop = top % (CellSize + 1) - (CellSize + 1);
        const int gridWidth = bounds.w + (CellSize + 1) * 2;
        const int gridHeight = bounds.h + (CellSize + 1) * 2;
        for (int dx = gridLeft; dx < gridWidth; dx += CellSize + 1) {
            renderer->drawLine(Colors::BLACK, dx, gridTop, dx, gridTop + gridHeight);
        }
        for (int dy = gridTop; dy < gridHeight; dy += CellSize + 1) {
            renderer->drawLine(Colors::BLACK, gridLeft, dy, gridLeft + gridWidth, dy);
        }
        auto control = _control->view();
        auto data = control->getTable("data");
        auto field = data->getTable("field");
        if (!field) return;
        
        const int cellLeft = -_offsetX / (CellSize + 1);
        const int cellTop = -_offsetY / (CellSize + 1);
        const int cellRight = cellLeft + bounds.w / (CellSize + 1) + 2;
        const int cellBottom = cellTop + bounds.h / (CellSize + 1) + 2;
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
                renderer->renderSprite(sprites->get("sprite0"), i, j, left + x * (CellSize + 1) + 1, top + y * (CellSize + 1) + 1);
            }
        }
    }
}
