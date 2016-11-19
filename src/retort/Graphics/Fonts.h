#pragma once
#include <common.h>

#include <SDL_ttf.h>

namespace Retort::Graphics {
    typedef TTF_Font Font;

    class Fonts {
        NONCOPYABLE(Fonts)

        std::shared_ptr<Font> _ubuntu14;

    public:
        Fonts();
        bool isValid() const;

        const std::shared_ptr<Font> ubuntu14() const;
    };
}
