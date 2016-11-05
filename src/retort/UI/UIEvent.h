#pragma once

#include <iostream>

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

        void dump(std::iostream &stream) const {
            switch (control) {
            case UIEvent::PipelineControl: stream << "PipelineControl::"; pipelineControlEvent.dump(stream); break;
            default: stream << "Unknown control type";
            }
        }
    };
}
