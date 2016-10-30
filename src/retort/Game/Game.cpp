#include "Game.h"

namespace Retort::Game {
    Game::Game() { }

    Feedback Game::consume(UIEvent e) {
        return Feedback::Continue;
    }

    Feedback Game::frameEnded() {
        return Feedback::Continue;
    }
}
