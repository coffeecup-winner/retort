#include <Game/Game.h>
#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Renderer.h>
#include <Graphics/SDLEnvironment.h>
#include <Graphics/Window.h>
#include <Input/SDLEventProducer.h>
#include <UI/UI.h>
#include <Utilities/Logging.h>
#include <Utilities/LoggingDecorator.h>

using namespace Retort::Game;
using namespace Retort::Graphics;
using namespace Retort::Input;
using namespace Retort::UI;
using namespace Retort::Utilities;

int main(int argc, char* argv[]) {
    Logging logging;

    log_INFO("Starting");

    SDLEnvironment environment;
    if (!environment.isValid()) {
        CRASH("Failed to initialize SDL: %s", SDL_GetError());
    }

    Window window("Hello World!", 640, 480);
    if (!window.isValid()) {
        CRASH("Failed to create window: %s", SDL_GetError());
    }

    auto renderer = std::make_shared<Renderer>(window);
    if (!renderer->isValid()) {
        CRASH("Failed to create renderer: %s", SDL_GetError());
    }

    log_INFO("Initialized SDL");

    auto sdlEvents = std::make_shared<SDLEventProducer>();
    auto ui = std::make_shared<UI>(renderer);
    auto uiEventLogger = std::make_shared<LoggingDecorator<UIEvent>>([](std::iostream &stream, const UIEvent &event) {
        return event.dump(stream);
    });
    auto game = std::make_shared<Game>(ui);

    log_INFO("Initialized game");

    sdlEvents->setConsumer(ui);
    ui->setConsumer(uiEventLogger);
    uiEventLogger->setConsumer(game);

    game->init();
    sdlEvents->run();

    log_INFO("Exiting");

    return 0;
}
