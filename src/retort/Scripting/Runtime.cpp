#include "Runtime.h"

namespace Retort::Scripting {
    Runtime::Runtime()
        : _state(luaL_newstate())
    {
        luaopen_base(_state);
    }

    Runtime::~Runtime() {
        lua_close(_state);
    }

    void Runtime::loadFile(const std::string &filepath) {
        if (luaL_loadfile(_state, filepath.c_str()) || lua_pcall(_state, 0, 0, 0)) {
            auto message = std::string("Failed to load a file: ") + lua_tostring(_state, -1);
            throw std::exception(message.c_str());
        }
    }
    
    void Runtime::invoke(const std::string &functionName) {
        lua_getglobal(_state, functionName.c_str());
        if (lua_pcall(_state, 0, 0, 0)) {
            auto message = std::string("Failed to invoke a function: ") + lua_tostring(_state, -1);
            throw std::exception(message.c_str());
        }
    }
}
