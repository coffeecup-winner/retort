#include "Panel.h"

namespace Retort::UI {
    void Panel::render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) {
        renderer->fillRect(getBackgroundColor(), getBounds());
    }
}
