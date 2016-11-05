#pragma once

#include <fstream>
#include <iomanip>
#include <time.h>

#include <SDL_log.h>

#define log_TRACE(msg, ...) (SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_DEBUG(msg, ...) (SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_INFO(msg, ...) (SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_WARN(msg, ...) (SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_ERROR(msg, ...) (SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_FATAL(msg, ...) (SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))

namespace Retort::Utilities {
    class Logging {
        std::ofstream _out;

    public:
        Logging();
    };
}
