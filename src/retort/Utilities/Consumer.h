#pragma once

#include <memory>

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
        Consumer(Consumer const &) = delete;
        Consumer &operator=(Consumer const &) = delete;

    public:
        Consumer();

        virtual Feedback consume(Event e) = 0;
        virtual Feedback frameEnded() = 0;
    };

    template <typename Event>
    Consumer<Event>::Consumer() { }
}