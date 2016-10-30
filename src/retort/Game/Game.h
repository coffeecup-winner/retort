#pragma once

#include <UI/UI.h>
#include <UI/UIEvent.h>
#include <Utilities/Consumer.h>

using namespace Retort::UI;
using namespace Retort::Utilities;

namespace Retort::Game {
    class Game : public Consumer<UIEvent> {
        Game(Game const &) = delete;
        Game &operator=(Game const &) = delete;

    public:
        Game();
        Feedback consume(UIEvent e) override;
        Feedback frameEnded() override;
    };
}
