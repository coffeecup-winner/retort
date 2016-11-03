#pragma once

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
    };
}
