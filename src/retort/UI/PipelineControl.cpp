#include "PipelineControl.h"

namespace Retort::UI {
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
