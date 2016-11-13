#pragma once
#include <common.h>

#include <Utilities/Consumer.h>
#include <Utilities/Producer.h>

namespace Retort::Utilities {
    template <typename InEvent, typename OutEvent>
    class Transformer
        : public Consumer<InEvent>
        , public Producer<OutEvent>
    {
    public:
        virtual ~Transformer();
        virtual Feedback frameEnded() override;
    };

    template <typename InEvent, typename OutEvent>
    Transformer<InEvent, OutEvent>::~Transformer() { }

    template <typename InEvent, typename OutEvent>
    Feedback Transformer<InEvent, OutEvent>::frameEnded() {
        return _consumer->frameEnded();
    }
}
