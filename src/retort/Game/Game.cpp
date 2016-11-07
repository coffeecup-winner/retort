#include "Game.h"

namespace Retort::Game {
    Game::Game()
        : _runtime(std::make_shared<Runtime>())
    { }

    Feedback Game::consume(const UIEvent &event) {
        switch (event.control) {
        case UIEvent::PipelineControl:
            switch (event.pipelineControlEvent.type) {
            case (PipelineControlEvent::CellClick):
                _runtime->invokeMethod(event.name, "onCellClick", event.pipelineControlEvent.cellClickX, event.pipelineControlEvent.cellClickY);
                break;
            default: crash("Unknown PipelineControl event");
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
        _runtime->loadFile("scripts/main.lua");
        _runtime->invokeFunction("onInit");
    }
}
