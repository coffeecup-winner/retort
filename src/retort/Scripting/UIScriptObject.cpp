#include "UIScriptObject.h"

#include <Scripting/GridControlScriptObject.h>
#include <UI/GridControl.h>

namespace Retort::Scripting {
    UIScriptObject::UIScriptObject(const std::shared_ptr<UI::UI> &ui, std::shared_ptr<Runtime> runtime)
        : ScriptObjectWrapper("__ui", ui)
        , _runtime(runtime)
    { }

    Feedback UIScriptObject::consume(const UIEvent &event) {
        auto ref = _controls.at(event.name);
		auto control = ref->view();
		auto events = control->getTable("events");
        switch (event.control) {
        case UIEvent::GridControl:
            switch (event.gridControlEvent.type) {
            case (GridControlEvent::CellClick):
				_runtime->invokeMethod(events, "cellClick", ref, event.gridControlEvent.cellClickX, event.gridControlEvent.cellClickY);
                break;
            default: CRASH("Unknown GridControl event");
            }
            break;
        default: CRASH("Unknown UI event from %s", event.name.c_str());
        }
        return Feedback::Continue;
    }

    Feedback UIScriptObject::frameEnded() {
        return Feedback::Continue;
    }

    void UIScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime) {
        runtime->assign("newGrid", this, [](lua_State *L) -> int {
            STACK_CHECK(L);
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            auto name = lua_tostring(L, 1);
            lua_newtable(L); // result
            lua_pushvalue(L, -1);
            auto control = Reference::create(L);
            closure.that->addControl(name, control);
            closure.runtime->assign("control", std::make_shared<GridControlScriptObject>(name, control));
            closure.runtime->assign("events", Runtime::EmptyTable);
            closure.runtime->assign("data", Runtime::EmptyTable);
            STACK_ASSERT(+1, L);
            return 1;
        });
        runtime->assign("controls", Runtime::EmptyTable);
        runtime->assign("show", this, [](lua_State *L) -> int {
            STACK_CHECK(L);
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            lua_getfield(L, 1, "control");
            auto obj = Runtime::unpackUserdata<GridControlScriptObject>(L, -1); // TODO: ControlScriptObject
            lua_pop(L, 1);
            closure.that->getObject()->show(obj->getObject());
            STACK_ASSERT(0, L);
            return 0;
        });
    }

    void UIScriptObject::addControl(const std::string &name, const std::shared_ptr<Reference> &ref) {
        _controls.insert(std::make_pair(name, ref));
    }
}
