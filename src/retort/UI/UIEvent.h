#pragma once

#include <iostream>

#include <UI/PipelineControlEvent.h>

namespace Retort::UI {
    struct UIEvent {
        std::string name;
        enum {
            PipelineControl,
        } control;
        union {
            PipelineControlEvent pipelineControlEvent;
        };

        UIEvent(const std::string &name, PipelineControlEvent event)
            : name(name)
            , control(UIEvent::PipelineControl)
            , pipelineControlEvent(event)
        { }

        void dump(std::iostream &stream) const {
            stream << "[" << name << "] ";
            switch (control) {
            case UIEvent::PipelineControl: stream << "PipelineControl::"; pipelineControlEvent.dump(stream); break;
            default: stream << "Unknown control type";
            }
        }
    };
}
