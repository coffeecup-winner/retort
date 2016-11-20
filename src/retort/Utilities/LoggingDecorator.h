#pragma once
#include <common.h>

#include <sstream>

#include <Utilities/Logging.h>
#include <Utilities/Transformer.h>

namespace Retort::Utilities {
    template <typename Event>
    class LoggingDecorator : public Transformer<Event, Event> {
        NONCOPYABLE(LoggingDecorator)

        typedef void (*LoggingDecoratorCallback)(std::iostream &stream, const Event &event);

        LoggingDecoratorCallback _callback;

    public:
        explicit LoggingDecorator(LoggingDecoratorCallback callback);
        virtual ~LoggingDecorator();
        Feedback consume(const Event &event) override;
    };

    template <typename Event>
    LoggingDecorator<Event>::LoggingDecorator(LoggingDecoratorCallback callback)
        : _callback(callback)
    { }

    template <typename Event>
    LoggingDecorator<Event>::~LoggingDecorator() { }

    template <typename Event>
    Feedback LoggingDecorator<Event>::consume(const Event &event) {
        std::stringstream sb;
        _callback(sb, event);
        log_INFO("Event: %s", sb.str().c_str());
        return _consumer->consume(event);
    }
}
