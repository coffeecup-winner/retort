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
        virtual ~Consumer();

        virtual Feedback consume(const Event &event) = 0;
        virtual Feedback frameEnded() = 0;
    };

    template <typename Event>
    Consumer<Event>::Consumer() { }

    template <typename Event>
    Consumer<Event>::~Consumer() { }
}
