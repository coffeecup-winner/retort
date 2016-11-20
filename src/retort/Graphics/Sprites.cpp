#include "Sprites.h"

namespace Retort::Graphics {
    Sprites::Sprites() {
        auto sprite = std::make_shared<Sprite>("sprites/sprite0.png");
        _sprites.insert(std::make_pair(sprite->getName(), sprite));
    }

    std::shared_ptr<Sprite> Sprites::get(const std::string & name) const {
        return _sprites.at(name);
    }
}
