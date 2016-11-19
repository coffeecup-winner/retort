#pragma once
#include <common.h>

#include <lua.hpp>

#include <Scripting/TableView.h>

namespace Retort::Scripting {

    class Reference {
        noncopyable(Reference)

        lua_State *_state;
        const int _ref;
        
    public:
        explicit Reference(lua_State *state, int ref);
        static std::shared_ptr<Reference> create(lua_State *L);
        ~Reference();
        std::shared_ptr<TableView> view();
    };
}
