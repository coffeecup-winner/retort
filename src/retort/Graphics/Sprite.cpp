#include "Sprite.h"

namespace Retort::Graphics {
    const std::string getFilenameWithoutExtension(const std::string &filepath) {
        char buf[_MAX_FNAME];
        if (_splitpath_s(filepath.c_str(), nullptr, 0, nullptr, 0, buf, _MAX_FNAME, nullptr, 0)) {
            CRASH("Failed to split path %s", filepath.c_str());
        }
        return std::string(buf);
    }

    Sprite::Sprite(const std::string &filepath)
        : _name(getFilenameWithoutExtension(filepath))
        , _surface(IMG_Load(filepath.c_str()))
    {
        if (!_surface) {
            CRASH("Failed to load %s: %s", filepath.c_str(), SDL_GetError());
        }
    }

    Sprite::~Sprite() {
        SDL_FreeSurface(_surface);
    }

    const std::string & Sprite::getName() const {
        return _name;
    }

    SDL_Surface * Sprite::get() const {
        return _surface;
    }
}
