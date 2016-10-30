#pragma once

#include <memory>

#include <SDL_ttf.h>

namespace Retort::Graphics {
    typedef TTF_Font Font;

    class Fonts {
        Fonts(const Fonts &) = delete;
        Fonts &operator=(const Fonts &) = delete;

        std::shared_ptr<Font> _ubuntu14;

    public:
        Fonts();
        bool isValid();

        const std::shared_ptr<Font> ubuntu14();
    };
}
