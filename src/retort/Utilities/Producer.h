#pragma once

#include <memory>

#include <Utilities/Consumer.h>

namespace Retort::Utilities {
    template <typename Event>
    class Consumer;

    template <typename Event>
    class Producer : public std::enable_shared_from_this<Producer<Event>> {
        Producer(Producer const &) = delete;
        Producer &operator=(Producer const &) = delete;

    protected:
        std::shared_ptr<Consumer<Event>> _consumer;

    public:
        Producer();
        virtual void setConsumer(std::shared_ptr<Consumer<Event>> consumer);
    };

    template <typename Event>
    Producer<Event>::Producer()
        : _consumer(std::shared_ptr<Consumer<Event>>(nullptr))
    { }

    template <typename Event>
    void Producer<Event>::setConsumer(std::shared_ptr<Consumer<Event>> consumer) {
        _consumer = consumer;
    }
}
