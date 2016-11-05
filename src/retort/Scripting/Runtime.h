#pragma once

#include <string>

#include <lua.hpp>

namespace Retort::Scripting {
    class Runtime {
        lua_State *_state;

    public:
        Runtime();
        ~Runtime();

        void loadFile(const std::string &filepath);
        void invoke(const std::string &functionName);
    };
}
