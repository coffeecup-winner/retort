#include "Panel.h"

namespace Retort::UI {
    Panel::Panel(const std::string &name)
        : Control(name)
    { }

    void Panel::render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) {
        renderer->fillRect(getBackgroundColor(), getBounds());
    }
}
