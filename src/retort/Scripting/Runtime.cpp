#include "Runtime.h"

namespace Retort::Scripting {
    void Runtime::push() { }

    Runtime::Runtime()
        : _state(luaL_newstate())
    {
        luaopen_base(_state);
        lua_pushnil(_state);
        lua_setglobal(_state, "print");

        lua_newtable(_state);
        push([](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_TRACE(message);
            return 0;
        });
        lua_setfield(_state, -2, "trace");
        push([](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_INFO(message);
            return 0;
        });
        lua_setfield(_state, -2, "info");
        push([](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_DEBUG(message);
            return 0;
        });
        lua_setfield(_state, -2, "debug");
        push([](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_WARN(message);
            return 0;
        });
        lua_setfield(_state, -2, "warn");
        push([](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_ERROR(message);
            return 0;
        });
        lua_setfield(_state, -2, "error");
        push([](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_FATAL(message);
            return 0;
        });
        lua_setfield(_state, -2, "fatal");
        lua_setglobal(_state, "log");
    }

    Runtime::~Runtime() {
        lua_close(_state);
    }

    void Runtime::loadFile(const std::string &filepath) {
        if (luaL_loadfile(_state, filepath.c_str()) || lua_pcall(_state, 0, 0, 0)) {
            crash("Failed to load a file: %s", lua_tostring(_state, -1));
        } else {
            log_INFO("Loaded script: %s", filepath.c_str());
        }
    }
}
