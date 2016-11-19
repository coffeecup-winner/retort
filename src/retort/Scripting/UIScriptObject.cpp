#include "UIScriptObject.h"

#include <Scripting/GridControlScriptObject.h>
#include <UI/GridControl.h>

namespace Retort::Scripting {
    UIScriptObject::UIScriptObject(const std::shared_ptr<UI::UI> &ui, std::shared_ptr<Runtime> runtime)
        : ScriptObjectWrapper("__ui", ui)
        , _runtime(runtime)
    { }

    Feedback UIScriptObject::consume(const UIEvent &event) {
        auto ref = _references.at(event.name);
        switch (event.control) {
        case UIEvent::GridControl:
            switch (event.gridControlEvent.type) {
            case (GridControlEvent::CellClick):
                _runtime->invokeMethod(ref, "cellClick", event.gridControlEvent.cellClickX, event.gridControlEvent.cellClickY);
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
            closure.runtime->assign("events", Runtime::EmptyTable);
            closure.runtime->assign("data", Runtime::EmptyTable);
            lua_getfield(L, -1, "data");
            auto data = Reference::create(L);
            closure.runtime->assign("control", std::make_shared<GridControlScriptObject>(name, data));
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
            lua_getfield(L, 1, "events");
            auto ref = Reference::create(L);
            closure.that->addReference(obj->getObject()->getName(), ref);
            closure.that->getObject()->show(obj->getObject());
            STACK_ASSERT(0, L);
            return 0;
        });
    }

    void UIScriptObject::addReference(const std::string & name, const std::shared_ptr<Reference> &ref) {
        _references.insert(std::make_pair(name, ref));
    }
}
