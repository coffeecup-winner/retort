#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include <Game/Game.h>
#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Renderer.h>
#include <Graphics/SDLEnvironment.h>
#include <Graphics/Window.h>
#include <Input/SDLEventProducer.h>
#include <UI/UI.h>
#include <Utilities/Logging.h>

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
        return 1;
    }

    Window window("Hello World!", 640, 480);
    if (!window.isValid()) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto renderer = std::make_shared<Renderer>(window);
    if (!renderer->isValid()) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    auto sdlEvents = std::make_shared<SDLEventProducer>();
    auto ui = std::make_shared<UI>(renderer);
    auto game = std::make_shared<Game>();
    game->init();

    sdlEvents->setConsumer(ui);
    ui->setConsumer(game);
    sdlEvents->run();

    log_INFO("Exiting");

    return 0;
}
