#include "Reference.h"

namespace Retort::Scripting {
    Reference::Reference(lua_State * state, int ref)
        : _state(state)
        , _ref(ref)
    { }

    std::shared_ptr<Reference> Reference::create(lua_State *L) {
        return std::make_shared<Reference>(L, luaL_ref(L, LUA_REGISTRYINDEX));
    }

    Reference::~Reference() {
        luaL_unref(_state, LUA_REGISTRYINDEX, _ref);
    }

    std::shared_ptr<TableView> Reference::view() {
        lua_rawgeti(_state, LUA_REGISTRYINDEX, _ref);
        return std::make_shared<TableView>(_state);
    }
}
