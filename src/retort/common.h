#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include <SDL_log.h>
#if defined(_DEBUG)
#include <lua.hpp>
#endif

#define log_TRACE(msg, ...) (SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_DEBUG(msg, ...) (SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_INFO(msg, ...) (SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_WARN(msg, ...) (SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_ERROR(msg, ...) (SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))
#define log_FATAL(msg, ...) (SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, msg, __VA_ARGS__))

#define CRASH(msg, ...) (log_FATAL(msg, __VA_ARGS__), doCrash())
[[noreturn]] void doCrash();

#define NONCOPYABLE(Type) \
    Type(Type const &) = delete; \
    Type &operator=(Type const &) = delete;

#if defined(_DEBUG)
#define STACK_CHECK(state) const int __stackBefore = lua_gettop(state)
#define STACK_ASSERT(expectedChange, state) assertStack(expectedChange, __stackBefore, state)
#define DUMP_STACK(state) dumpStack(state)
void assertStack(const int expectedChange, const int stackBefore, lua_State *L);
void dumpStack(lua_State *L);
#else
#define STACK_CHECK(state)
#define STACK_ASSERT(expectedChange, state)
#define STACK_DUMP(state)
#endif
