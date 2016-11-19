#pragma once
#include <common.h>

#include <Utilities/Producer.h>

namespace Retort::Utilities {
    enum Feedback {
        Continue,
        Stop,
    };

    template <typename Event>
    class Producer;

    template <typename Event>
    class Consumer {
        NONCOPYABLE(Consumer)

    public:
        Consumer();
        virtual ~Consumer();

        virtual Feedback consume(const Event &event) = 0;
        virtual Feedback frameEnded() = 0;
    };

    template <typename Event>
    Consumer<Event>::Consumer() { }

    template <typename Event>
    Consumer<Event>::~Consumer() { }
}
