#pragma once
#include <common.h>

#include <Graphics/Renderer.h>
#include <Graphics/Sprites.h>
#include <UI/UIEvent.h>
#include <Utilities/Transformer.h>

using namespace Retort::Graphics;
using namespace Retort::UI;
using namespace Retort::Utilities;

namespace Retort::UI {
    class Control : public Transformer<SDL_Event, UIEvent> {
        NONCOPYABLE(Control)

        std::string _name;
		Rect _bounds = { 0, 0, 0, 0 };
        Color _backgroundColor = Colors::WHITE;
        int _mouseDownX = 0;
        int _mouseDownY = 0;

    protected:
        explicit Control(const std::string &name);
        int getMouseDownX() const;
        int getMouseDownY() const;

    public:
        virtual ~Control();
        const std::string &getName() const;
        const Rect &getBounds() const;
        const Color &getBackgroundColor() const;

        Feedback consume(const SDL_Event &event) override;
        virtual void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> &fonts, std::shared_ptr<Sprites> &sprites) = 0;

        void move(int x, int y);
        void resize(int w, int h);
    };
}
