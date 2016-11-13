#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include <SDL_assert.h>
#include <SDL_log.h>

#define log_TRACE(msg, ...) (SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_DEBUG(msg, ...) (SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_INFO(msg, ...) (SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_WARN(msg, ...) (SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_ERROR(msg, ...) (SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_FATAL(msg, ...) (SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))

#ifdef _DEBUG
#define quit() (SDL_TriggerBreakpoint())
#else
#define quit() (exit(1))
#endif

#define crash(msg, ...) {\
    log_FATAL(msg, __VA_ARGS__);\
    quit();\
}
