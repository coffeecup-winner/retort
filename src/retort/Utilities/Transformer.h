#pragma once

#include <Utilities/Consumer.h>
#include <Utilities/Producer.h>

namespace Retort::Utilities {
    template <typename InEvent, typename OutEvent>
    class Transformer
        : public Consumer<InEvent>
        , public Producer<OutEvent>
    {
    public:
        virtual Feedback frameEnded() override;
    };

    template <typename InEvent, typename OutEvent>
    Feedback Transformer<InEvent, OutEvent>::frameEnded() {
        return _consumer->frameEnded();
    }
}
