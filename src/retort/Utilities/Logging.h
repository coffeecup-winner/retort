#pragma once
#include <common.h>

#include <fstream>
#include <iomanip>
#include <time.h>

namespace Retort::Utilities {
    class Logging {
        NONCOPYABLE(Logging)

        std::ofstream _out;

    public:
        Logging();
    };
}
