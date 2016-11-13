#include "UIScriptObject.h"

#include <Scripting/GridControlScriptObject.h>
#include <UI/GridControl.h>

namespace Retort::Scripting {
    UIScriptObject::UIScriptObject(const std::shared_ptr<UI::UI> &ui)
        : ScriptObjectWrapper("__ui", ui)
    { }

    void UIScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime) {
        runtime->assign("newGrid", this, [](lua_State *L) -> int {
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            auto name = lua_tostring(L, 1);
            closure.runtime->push(std::make_shared<GridControlScriptObject>(name));
            return 1;
        });
        runtime->assign("show", this, [](lua_State *L) -> int {
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            auto obj = Runtime::unpackUserdata<GridControlScriptObject>(L, 1); // TODO: ControlScriptObject
            closure.that->getObject()->show(obj->getObject());
            return 0;
        });
    }
}
