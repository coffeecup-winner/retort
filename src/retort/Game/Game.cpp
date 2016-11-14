#include "Game.h"

namespace Retort::Game {
    Game::Game(std::shared_ptr<UI::UI> ui)
        : _runtime(std::make_shared<Runtime>())
        , _ui(std::make_shared<UIScriptObject>(ui, _runtime))
    { }

    Feedback Game::consume(const UIEvent & event) {
        return _ui->consume(event);
    }

    Feedback Game::frameEnded() {
        return _ui->frameEnded();
    }

    void Game::init() {
        _runtime->assign("ui", _ui);
        _runtime->loadFile("scripts/main.lua");
        _runtime->invokeFunction("onInit");
    }
}
