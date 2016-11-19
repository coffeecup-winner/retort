#pragma once
#include <common.h>

#include <lua.hpp>

namespace Retort::Scripting {
    class TableView {
        noncopyable(TableView)

        lua_State *_state;

    public:
        explicit TableView(lua_State *state);
        ~TableView();
        std::shared_ptr<TableView> getTable(const std::string &name);
        std::shared_ptr<TableView> getTable(const int i);
    };
}
