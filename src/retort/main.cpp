#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include <Graphics/Colors.h>
#include <Graphics/Fonts.h>
#include <Graphics/Renderer.h>
#include <Graphics/SDLEnvironment.h>
#include <Graphics/Window.h>
#include <Input/SDLEventProducer.h>
#include <UI/UI.h>

using namespace Retort::Graphics;
using namespace Retort::Input;
using namespace Retort::UI;

int main(int argc, char* argv[]) {
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

    auto ui = std::make_shared<UI>(renderer);
    auto sdlEvents = std::make_shared<SDLEventProducer>();
    sdlEvents->setConsumer(ui);
    sdlEvents->run();

    return 0;
}
