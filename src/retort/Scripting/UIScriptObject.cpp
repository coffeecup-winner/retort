#include "UIScriptObject.h"

namespace Retort::Scripting {
    UIScriptObject::UIScriptObject()
        : ScriptObject("__ui")
    { }

    void UIScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime)
    {
        runtime->assign("newGrid", this, [](lua_State *L) -> int {
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            closure.runtime->push(nullptr);
            return 1;
        });
    }
}
