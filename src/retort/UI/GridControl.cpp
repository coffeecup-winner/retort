#include "GridControl.h"

namespace Retort::UI {
    GridControl::GridControl(const std::string &name, std::shared_ptr<Reference> data)
        : Control(name)
        , _control(data)
    { }

    Feedback GridControl::consume(const SDL_Event &event) {
        Control::consume(event);
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            auto click = UIEvent(getName(), GridControlEvent(getMouseDownX() / 32, getMouseDownY() / 32));
            _consumer->consume(click);
        }
        return Feedback::Continue;
    }

    void GridControl::render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts, std::shared_ptr<Sprites> sprites) {
        renderer->fillRect(getBackgroundColor(), getBounds());
        auto bounds = getBounds();
        for (int dx = bounds.x; dx < bounds.w; dx += 32) {
            renderer->drawLine(Colors::BLACK, bounds.x + dx, bounds.y, bounds.x + dx, bounds.y + bounds.h);
        }
        for (int dy = bounds.y; dy < bounds.h; dy += 32) {
            renderer->drawLine(Colors::BLACK, bounds.x, bounds.y + dy, bounds.x + bounds.w, bounds.y + dy);
        }
        auto control = _control->view();
        auto data = control->getTable("data");
        auto field = data->getTable("field");
        if (!field) return;
        for (int x = 0; x < bounds.w / 32; ++x) {
            auto column = field->getTable(x);
            if (!column) continue;
            for (int y = 0; y < bounds.h / 32; ++y) {
                auto cell = column->getTable(y);
                if (cell) {
                    auto name = cell->getString("name");
                    int i = 0, j = 0;
                    if (name == "start") {
                        i = 1;
                    } else if (name == "end") {
                        j = 1;
                    }
                    renderer->renderSprite(sprites->get("sprite0"), i, j, x * 32, y * 32);
                }
            }
        }
    }
}
