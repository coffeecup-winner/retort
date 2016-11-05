#include "Game.h"

namespace Retort::Game {
    Game::Game()
        : _runtime(std::make_shared<Runtime>())
    { }

    Feedback Game::consume(const UIEvent &event) {
        return Feedback::Continue;
    }

    Feedback Game::frameEnded() {
        return Feedback::Continue;
    }

    void Game::init() {
        _runtime->loadFile("scripts/main.lua");
        _runtime->invoke("onInit");
    }
}
