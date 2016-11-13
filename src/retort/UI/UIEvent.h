#pragma once
#include <common.h>

#include <UI/GridControlEvent.h>

namespace Retort::UI {
    struct UIEvent {
        std::string name;
        enum {
            GridControl,
        } control;
        union {
            GridControlEvent gridControlEvent;
        };

        UIEvent(const std::string &name, GridControlEvent event)
            : name(name)
            , control(UIEvent::GridControl)
            , gridControlEvent(event)
        { }

        void dump(std::iostream &stream) const {
            stream << "[" << name << "] ";
            switch (control) {
            case UIEvent::GridControl: stream << "GridControl::"; gridControlEvent.dump(stream); break;
            default: stream << "Unknown control type";
            }
        }
    };
}
