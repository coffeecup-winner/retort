#include "PipelineControl.h"

namespace Retort::UI {
    PipelineControl::PipelineControl(const std::string &name)
        : Control(name)
    { }

    Feedback PipelineControl::consume(const SDL_Event &event) {
        Control::consume(event);
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
            auto click = UIEvent(getName(), PipelineControlEvent(getMouseDownX() / 32, getMouseDownY() / 32));
            _consumer->consume(click);
        }
        return Feedback::Continue;
    }

    void PipelineControl::render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) {
        renderer->fillRect(getBackgroundColor(), getBounds());
        auto bounds = getBounds();
        for (int dx = bounds.x; dx < bounds.w; dx += 32) {
            renderer->drawLine(Colors::BLACK, bounds.x + dx, bounds.y, bounds.x + dx, bounds.y + bounds.h);
        }
        for (int dy = bounds.y; dy < bounds.h; dy += 32) {
            renderer->drawLine(Colors::BLACK, bounds.x, bounds.y + dy, bounds.x + bounds.w, bounds.y + dy);
        }
    }
}
