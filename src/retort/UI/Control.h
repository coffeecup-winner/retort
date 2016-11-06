#pragma once

#include <memory>

#include <Graphics/Renderer.h>
#include <UI/UIEvent.h>
#include <Utilities/Transformer.h>

using namespace Retort::Graphics;
using namespace Retort::UI;
using namespace Retort::Utilities;

namespace Retort::UI {
    class Control : public Transformer<SDL_Event, UIEvent> {
        Control(Control const &) = delete;
        Control &operator=(Control const &) = delete;

        std::string _name;
        Rect _bounds;
        Color _backgroundColor;
        int _mouseDownX;
        int _mouseDownY;

    protected:
        explicit Control(const std::string &name);
        int getMouseDownX() const;
        int getMouseDownY() const;

    public:
        virtual ~Control();
        const std::string &getName() const;
        const Rect &getBounds() const;
        const Color &getBackgroundColor() const;

        virtual Feedback consume(const SDL_Event &event) override;
        virtual void render(std::shared_ptr<Renderer> renderer, std::shared_ptr<Fonts> fonts) = 0;

        void move(int x, int y);
        void resize(int w, int h);
    };
}
