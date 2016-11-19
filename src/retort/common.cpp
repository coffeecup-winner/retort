#include <common.h>

#include <SDL_assert.h>

void doCrash() {
#if defined(_DEBUG)
    SDL_TriggerBreakpoint();
#endif
    exit(1);
}

#if defined(_DEBUG)
void assertStack(const int expectedChange, const int stackBefore, lua_State *L) {
    const int change = lua_gettop(L) - stackBefore;
    if (change != expectedChange) {
        CRASH("Stack disbalance, expected %s%d, was %s%d", expectedChange > 0 ? "+" : "", expectedChange, change > 0 ? "+" : "", change);
    }
}

void dumpStack(lua_State *L) {
    STACK_CHECK(L);
    log_INFO("Stack dump:");
    const int top = lua_gettop(L);
    for (int i = 1; i <= top; i++) {
        const int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING:
            log_INFO("'%s'", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            log_INFO(lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            log_INFO("%g", lua_tonumber(L, i));
            break;
        case LUA_TTABLE:
            log_INFO("Table:");
            lua_pushnil(L);
            while (lua_next(L, i)) {
                if (lua_type(L, -2) == LUA_TSTRING) {
                    log_INFO("  %s: %s\n", lua_tostring(L, -2), lua_typename(L, lua_type(L, -1)));
                } else {
                    log_INFO("  %g: %s\n", lua_tonumber(L, -2), lua_typename(L, lua_type(L, -1)));
                }
                lua_pop(L, 1);
            }
            break;
        default:
            log_INFO("<%s>", lua_typename(L, t));
            break;
        }
    }
    STACK_ASSERT(0, L);
}
#endif
