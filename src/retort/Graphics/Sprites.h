#pragma once
#include <common.h>

#include <map>

#include <Graphics/Sprite.h>

namespace Retort::Graphics {
    class Sprites {
        NONCOPYABLE(Sprites)

        std::map<std::string, std::shared_ptr<Sprite>> _sprites = {};

    public:
        Sprites();
        std::shared_ptr<Sprite> get(const std::string &name) const;
    };
}
