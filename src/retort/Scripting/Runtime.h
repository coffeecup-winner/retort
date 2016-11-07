#pragma once

#include <cstdint>
#include <memory>
#include <map>

#include <lua.hpp>

#include <Scripting/ScriptObject.h>
#include <Utilities/Logging.h>

namespace Retort::Scripting {
    class ScriptObject;

    class Runtime : public std::enable_shared_from_this<Runtime> {
        lua_State *_state;
        std::map<std::intptr_t, std::shared_ptr<ScriptObject>> _managedObjects;

        template <typename ...Types>
        void pushArgs();
        template <typename ...Types>
        void pushArgs(bool b, Types... params);
        template <typename ...Types>
        void pushArgs(std::nullptr_t n, Types... params);
        template <typename ...Types>
        void pushArgs(int i, Types... params);
        template <typename ...Types>
        void pushArgs(double d, Types... params);
        template <typename ...Types>
        void pushArgs(const std::string &s, Types... params);
        template <typename ...Types>
        void pushArgs(lua_CFunction f, Types... params);
        template <typename ...Types>
        void pushArgs(std::shared_ptr<ScriptObject> o, Types... params);
        
        void push(bool b);
        void push(std::nullptr_t n);
        void push(int i);
        void push(double d);
        void push(const std::string &s);
        void push(lua_CFunction f);
        void push(std::shared_ptr<ScriptObject> &o);
        void assign(const std::string &name);

    public:
        Runtime();
        ~Runtime();

        void assign(const std::string &name, bool b);
        void assign(const std::string &name, std::nullptr_t n);
        void assign(const std::string &name, int i);
        void assign(const std::string &name, double d);
        void assign(const std::string &name, const std::string &s);
        void assign(const std::string &name, lua_CFunction f);
        void assign(const std::string &name, std::shared_ptr<ScriptObject> o);
        void loadFile(const std::string &filepath);
        template <typename ...Types>
        void invokeFunction(const std::string &functionName, Types... params);
        template <typename ...Types>
        void invokeMethod(const std::string &object, const std::string &methodName, Types... params);
    };

    template <typename ...Types>
    inline void Runtime::pushArgs() { }

    template <typename ...Types>
    inline void Runtime::pushArgs(bool b, Types... params) {
        push(b);
        pushArgs(params...);
    }

    template <typename ...Types>
    inline void Runtime::pushArgs(std::nullptr_t n, Types... params) {
        push(n);
        pushArgs(params...);
    }

    template <typename ...Types>
    inline void Runtime::pushArgs(int i, Types... params) {
        push(i);
        pushArgs(params...);
    }

    template <typename ...Types>
    inline void Runtime::pushArgs(double d, Types... params) {
        push(d);
        pushArgs(params...);
    }

    template <typename ...Types>
    inline void Runtime::pushArgs(const std::string &s, Types... params) {
        push(s);
        pushArgs(params...);
    }

    template <typename ...Types>
    inline void Runtime::pushArgs(lua_CFunction f, Types... params) {
        push(f);
        pushArgs(params...);
    }

    template<typename ...Types>
    inline void Runtime::pushArgs(std::shared_ptr<ScriptObject> o, Types ...params)
    {
        push(o);
        pushArgs(params...);
    }

    template <typename ...Types>
    void Runtime::invokeFunction(const std::string &functionName, Types... params) {
        switch (lua_getglobal(_state, functionName.c_str())) {
        case LUA_TNIL: crash("Global function %s does not exist", functionName.c_str());
        case LUA_TFUNCTION: break;
        default: crash("Global variable %s is not a function", functionName.c_str());
        }
        pushArgs(params...);
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
        pushArgs(params...);
        if (lua_pcall(_state, constexpr { sizeof...(Types) }, 0, 0)) {
            crash("Failed to to invoke a function: %s", lua_tostring(_state, -1));
        }
    }
}
