#pragma once

#include <UI/PipelineControlEvent.h>

namespace Retort::UI {
    struct UIEvent {
        enum {
            PipelineControl,
        } control;
        union {
            PipelineControlEvent pipelineControlEvent;
        };

        explicit UIEvent(PipelineControlEvent event)
            : control(UIEvent::PipelineControl)
            , pipelineControlEvent(event)
        { }
    };
}
