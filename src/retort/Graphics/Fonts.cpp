#include "Fonts.h"

namespace Retort::Graphics {
    Fonts::Fonts()
        : _ubuntu14(std::shared_ptr<Font>(TTF_OpenFont("fonts/Ubuntu-R.ttf", 14), TTF_CloseFont))
    {
		if (_ubuntu14.get() == nullptr) {
			CRASH("Failed to load Ubuntu 14 font");
		}
	}

    const std::shared_ptr<Font> Fonts::ubuntu14() const {
        return _ubuntu14;
    }
}
