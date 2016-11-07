#pragma once

#include <lua.hpp>

#include <Utilities/Logging.h>

namespace Retort::Scripting {
    class Runtime {
        lua_State *_state;

    private:
        void push();
        template <typename ...Types>
        void push(bool b, Types... params);
        template <typename ...Types>
        void push(decltype(nullptr), Types... params);
        template <typename ...Types>
        void push(int i, Types... params);
        template <typename ...Types>
        void push(double d, Types... params);
        template <typename ...Types>
        void push(const std::string &s, Types... params);
        template <typename ...Types>
        void push(lua_CFunction f, Types... params);

    public:
        Runtime();
        ~Runtime();

        void loadFile(const std::string &filepath);
        template <typename ...Types>
        void invokeFunction(const std::string &functionName, Types... params);
        template <typename ...Types>
        void invokeMethod(const std::string &object, const std::string &methodName, Types... params);
    };

    template <typename ...Types>
    void Runtime::push(bool b, Types... params) {
        lua_pushboolean(_state, b);
        push(params...);
    }

    template <typename ...Types>
    void Runtime::push(decltype(nullptr), Types... params) {
        lua_pushnil(_state);
        push(params...);
    }

    template <typename ...Types>
    void Runtime::push(int i, Types... params) {
        lua_pushinteger(_state, i);
        push(params...);
    }

    template <typename ...Types>
    void Runtime::push(double d, Types... params) {
        lua_pushnumber(_state, d);
        push(params...);
    }

    template <typename ...Types>
    void Runtime::push(const std::string &s, Types... params) {
        lua_pushstring(_state, s.c_str());
        push(params...);
    }

    template <typename ...Types>
    void Runtime::push(lua_CFunction f, Types... params) {
        lua_pushcfunction(_state, f);
        push(params...);
    }

    template <typename ...Types>
    void Runtime::invokeFunction(const std::string &functionName, Types... params) {
        switch (lua_getglobal(_state, functionName.c_str())) {
        case LUA_TNIL: crash("Global function %s does not exist", functionName.c_str());
        case LUA_TFUNCTION: break;
        default: crash("Global variable %s is not a function", functionName.c_str());
        }
        push(params...);
        if (lua_pcall(_state, constexpr { sizeof...(Types) }, 0, 0)) {
            crash("Failed to to invoke a function: %s", lua_tostring(_state, -1));
        }
    }

    template <typename ...Types>
    void Runtime::invokeMethod(const std::string &object, const std::string &methodName, Types... params) {
        switch (int type = lua_getglobal(_state, object.c_str()))
        {
        case LUA_TNIL: crash("Global object %s not found", object.c_str());
        case LUA_TTABLE: break;
        default: crash("Global object %s is of type %s, not table", object.c_str(), lua_typename(_state, type));
        }
        switch (lua_getfield(_state, -1, methodName.c_str())) {
        case LUA_TNIL: crash("Method %s.%s does not exist", object.c_str(), methodName.c_str());
        case LUA_TFUNCTION: break;
        default: crash("Member %s.%s is not a function", object.c_str(), methodName.c_str());
        }
        push(params...);
        if (lua_pcall(_state, constexpr { sizeof...(Types) }, 0, 0)) {
            crash("Failed to to invoke a function: %s", lua_tostring(_state, -1));
        }
    }
}
