#include "Runtime.h"

namespace Retort::Scripting {
    Runtime::Runtime()
        : _state(luaL_newstate())
    {
        luaopen_base(_state);
        lua_pop(_state, 1);
        lua_pushnil(_state);
        assign("print");

        lua_newtable(_state);
        assign("trace", [](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_TRACE(message);
            return 0;
        });
        assign("info", [](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_INFO(message);
            return 0;
        });
        assign("debug", [](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_DEBUG(message);
            return 0;
        });
        assign("warn", [](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_WARN(message);
            return 0;
        });
        assign("error", [](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_ERROR(message);
            return 0;
        });
        assign("fatal", [](lua_State *L) -> int {
            const char *message = lua_tostring(L, 1);
            log_FATAL(message);
            return 0;
        });
        assign("log");
    }

    Runtime::~Runtime() {
        lua_close(_state);
    }

    int Runtime::EmptyFunction(lua_State *L) {
        return 0;
    }

    void Runtime::EmptyTable(std::shared_ptr<Runtime> table) { }

    void Runtime::push(bool b) {
        lua_pushboolean(_state, b);
    }

    void Runtime::push(std::nullptr_t n) {
        lua_pushnil(_state);
    }

    void Runtime::push(int i) {
        lua_pushinteger(_state, i);
    }

    void Runtime::push(double d) {
        lua_pushnumber(_state, d);
    }

    void Runtime::push(const std::string & s) {
        lua_pushstring(_state, s.c_str());
    }

    void Runtime::push(lua_CFunction f) {
        lua_pushcfunction(_state, f);
    }

    void Runtime::push(lua_CFunction f, int upvaluesCount) {
        lua_pushcclosure(_state, f, upvaluesCount);
    }

    void Runtime::push(std::shared_ptr<ScriptObject> o) {
        new (lua_newuserdata(_state, sizeof(o))) std::shared_ptr<ScriptObject>(o);
        log_INFO("[GC] allocated a new object of type %s: %p", o->getMetaTableName().c_str(), o.get());

        if (!luaL_getmetatable(_state, o->getMetaTableName().c_str())) {
            log_INFO("Creating metatable for type %s", o->getMetaTableName().c_str());
            lua_pop(_state, 1);
            luaL_newmetatable(_state, o->getMetaTableName().c_str());
            lua_newtable(_state);
            o->fillMetaTable(this->shared_from_this());
            assign("__index");
            assign("__gc", [](lua_State *L) -> int {
                if (lua_type(L, -1) != LUA_TUSERDATA) {
                    CRASH("[GC] trying to collect non-userdata object");
                }
                auto obj = reinterpret_cast<std::shared_ptr<ScriptObject> *>(lua_touserdata(L, 1));
                log_INFO("[GC] collected %p", obj->get());
                obj->reset();
                return 0;
            });
        }
        lua_setmetatable(_state, -2);
    }

    void Runtime::push(TableFunction f) {
        lua_newtable(_state);
        f(shared_from_this());
    }

	void Runtime::push(std::shared_ptr<Reference> r) {
		auto view = r->view();
		lua_pushvalue(_state, -1);
	}

    void Runtime::assign(const std::string &name) {
        if (lua_gettop(_state) == 1) {
            lua_setglobal(_state, name.c_str());
        }
        else {
            lua_setfield(_state, -2, name.c_str());
        }
    }

    void Runtime::assign(const std::string &name, bool b) {
        push(b);
        assign(name);
    }

    void Runtime::assign(const std::string &name, std::nullptr_t n) {
        push(n);
        assign(name);
    }

    void Runtime::assign(const std::string &name, int i) {
        push(i);
        assign(name);
    }

    void Runtime::assign(const std::string &name, double d) {
        push(d);
        assign(name);
    }

    void Runtime::assign(const std::string &name, const std::string &s) {
        push(s);
        assign(name);
    }

    void Runtime::assign(const std::string &name, lua_CFunction f) {
        push(f);
        assign(name);
    }

    void Runtime::assign(const std::string &name, ScriptObject *that, lua_CFunction f) {
        push(reinterpret_cast<int>(this));
        push(reinterpret_cast<int>(that));
        push(f, 2);
        assign(name);
    }

    void Runtime::assign(const std::string &name, std::shared_ptr<ScriptObject> o) {
        push(o);
        assign(name);
    }

    void Runtime::assign(const std::string & name, TableFunction f) {
        push(f);
        assign(name);
    }

    void Runtime::loadFile(const std::string &filepath) {
        if (luaL_loadfile(_state, filepath.c_str()) || lua_pcall(_state, 0, 0, 0)) {
            CRASH("Failed to load a file: %s", lua_tostring(_state, -1));
        } else {
            log_INFO("Loaded script: %s", filepath.c_str());
        }
    }
}
