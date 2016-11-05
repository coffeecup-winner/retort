#pragma once

#include <iostream>

namespace Retort::UI {
    struct PipelineControlEvent {
        enum {
            CellClick,
        } type;
        union {
            struct {
                int cellClickX;
                int cellClickY;
            };
        };

        PipelineControlEvent(int x, int y)
            : type(PipelineControlEvent::CellClick)
            , cellClickX(x)
            , cellClickY(y)
        { }

        void dump(std::iostream &stream) const {
            switch (type) {
            case PipelineControlEvent::CellClick: stream << "CellClick (" << cellClickX << ", " << cellClickY << ")"; break;
            default: stream << "Unknown event type";
            }
        }
    };
}
