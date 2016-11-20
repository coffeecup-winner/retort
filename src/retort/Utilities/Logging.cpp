#include "Logging.h"

namespace Retort::Utilities {
    Logging::Logging()
        : _out(std::ofstream())
    {
        _out.open("retort.log");
        SDL_LogSetOutputFunction([] (void *userdata, int category, SDL_LogPriority priority, const char *message) {
            auto time = std::time(nullptr);
			tm buf = {};
            const char *priorityName = nullptr;
            switch (priority) {
            case SDL_LOG_PRIORITY_VERBOSE: priorityName = "TRACE"; break;
            case SDL_LOG_PRIORITY_DEBUG: priorityName = "DEBUG"; break;
            case SDL_LOG_PRIORITY_INFO: priorityName = "INFO"; break;
            case SDL_LOG_PRIORITY_WARN: priorityName = "WARN"; break;
            case SDL_LOG_PRIORITY_ERROR: priorityName = "ERROR"; break;
            case SDL_LOG_PRIORITY_CRITICAL: priorityName = "FATAL"; break;
            default: CRASH("Unknown log priority");
            }
            localtime_s(&buf, &time);
            static_cast<Logging *>(userdata)->_out
                << std::put_time(&buf, "[%H:%M:%S] [")
                << priorityName
                << "] "
                << message
                << std::endl;
			static_cast<Logging *>(userdata)->_out.flush();
        }, this);
    }
}
