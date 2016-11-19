#include "TableView.h"

namespace Retort::Scripting {
    TableView::TableView(lua_State * state)
        : _state(state)
    { }

    TableView::~TableView() {
        lua_pop(_state, 1);
    }

    std::shared_ptr<TableView> TableView::getTable(const std::string &name) {
        STACK_CHECK(_state);
        int type = lua_getfield(_state, -1, name.c_str());
        if (type == LUA_TNIL) {
            lua_pop(_state, 1);
            STACK_ASSERT(0, _state);
            return nullptr;
        }
        if (type != LUA_TTABLE) {
            CRASH("Type mismatch, expected table, got %s", lua_typename(_state, type));
        }
        STACK_ASSERT(+1, _state);
        return std::make_shared<TableView>(_state);
    }

    std::shared_ptr<TableView> TableView::getTable(const int i) {
        STACK_CHECK(_state);
        int type = lua_geti(_state, -1, i);
        if (type == LUA_TNIL) {
            lua_pop(_state, 1);
            STACK_ASSERT(0, _state);
            return nullptr;
        }
        if (type != LUA_TTABLE) {
            CRASH("Type mismatch, expected table, got %s", lua_typename(_state, type));
        }
        STACK_ASSERT(+1, _state);
        return std::make_shared<TableView>(_state);
    }
}
