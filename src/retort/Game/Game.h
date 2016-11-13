#pragma once
#include <common.h>

#include <Scripting/Runtime.h>
#include <Scripting/UIScriptObject.h>
#include <UI/UI.h>
#include <UI/UIEvent.h>
#include <Utilities/Consumer.h>

using namespace Retort::Scripting;
using namespace Retort::UI;
using namespace Retort::Utilities;

namespace Retort::Game {
    class Game : public Consumer<UIEvent> {
        Game(Game const &) = delete;
        Game &operator=(Game const &) = delete;

        std::shared_ptr<Runtime> _runtime;
        std::shared_ptr<UI::UI> _ui;

    public:
        Game(std::shared_ptr<UI::UI> ui);
        Feedback consume(const UIEvent &event) override;
        Feedback frameEnded() override;
        void init();
    };
}
