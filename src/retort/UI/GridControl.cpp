#include "GridControl.h"

namespace Retort::UI {
    GridControl::GridControl(const std::string &name, std::shared_ptr<Reference> &control)
        : Control(name)
        , _control(control)
    { }

    Feedback GridControl::consume(const SDL_Event &event) {
        Control::consume(event);
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            auto click = UIEvent(getName(), GridControlEvent(getMouseDownX() / (CellSize + 1), getMouseDownY() / (CellSize + 1)));
            _consumer->consume(click);
        }
        return Feedback::Continue;
    }

    void GridControl::render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> &fonts, std::shared_ptr<Sprites> &sprites) {
        renderer->fillRect(getBackgroundColor(), getBounds());
        auto bounds = getBounds();
        for (int dx = bounds.x; dx < bounds.w; dx += CellSize + 1) {
            renderer->drawLine(Colors::BLACK, bounds.x + dx, bounds.y, bounds.x + dx, bounds.y + bounds.h);
        }
        for (int dy = bounds.y; dy < bounds.h; dy += CellSize + 1) {
            renderer->drawLine(Colors::BLACK, bounds.x, bounds.y + dy, bounds.x + bounds.w, bounds.y + dy);
        }
        auto control = _control->view();
        auto data = control->getTable("data");
        auto field = data->getTable("field");
        if (!field) return;
        for (int x = 0; x < bounds.w / CellSize; ++x) {
            auto column = field->getTable(x);
            if (!column) continue;
            for (int y = 0; y < bounds.h / CellSize; ++y) {
                auto cell = column->getTable(y);
                if (!cell) continue;
                auto name = cell->getString("name");
                int i = 0, j = 0;
                if (name == "start") {
                    i = 1;
                } else if (name == "end") {
                    j = 1;
                }
                renderer->renderSprite(sprites->get("sprite0"), i, j, x * (CellSize + 1) + 1, y * (CellSize + 1) + 1);
            }
        }
    }
}
