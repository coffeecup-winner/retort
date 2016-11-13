#include "Game.h"

namespace Retort::Game {
    Game::Game(std::shared_ptr<UI::UI> ui)
        : _runtime(std::make_shared<Runtime>())
        , _ui(ui)
    { }

    Feedback Game::consume(const UIEvent &event) {
        switch (event.control) {
        case UIEvent::GridControl:
            switch (event.gridControlEvent.type) {
            case (GridControlEvent::CellClick):
                _runtime->invokeMethod(event.name, "onCellClick", event.gridControlEvent.cellClickX, event.gridControlEvent.cellClickY);
                break;
            default: crash("Unknown GridControl event");
            }
            break;
        default: crash("Unknown UI event from %s", event.name.c_str())
        }
        return Feedback::Continue;
    }

    Feedback Game::frameEnded() {
        return Feedback::Continue;
    }

    void Game::init() {
        _runtime->assign("ui", std::make_shared<UIScriptObject>(_ui));
        _runtime->loadFile("scripts/main.lua");
        _runtime->invokeFunction("onInit");
    }
}
