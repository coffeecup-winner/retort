#include "Game.h"

namespace Retort::Game {
    Game::Game() { }

    Feedback Game::consume(const UIEvent &event) {
        return Feedback::Continue;
    }

    Feedback Game::frameEnded() {
        return Feedback::Continue;
    }
}
