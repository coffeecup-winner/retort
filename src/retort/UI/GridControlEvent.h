#pragma once
#include <common.h>

namespace Retort::UI {
    struct GridControlEvent {
        enum {
            CellClick,
        } type;
        union {
            struct {
                int cellClickX;
                int cellClickY;
            };
        };

        GridControlEvent(int x, int y)
            : type(GridControlEvent::CellClick)
            , cellClickX(x)
            , cellClickY(y)
        { }

        void dump(std::iostream &stream) const {
            switch (type) {
            case GridControlEvent::CellClick: stream << "CellClick (" << cellClickX << ", " << cellClickY << ")"; break;
            default: stream << "Unknown event type";
            }
        }
    };
}
