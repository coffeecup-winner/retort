#include "UIScriptObject.h"

#include <Scripting/GridControlScriptObject.h>
#include <UI/GridControl.h>

namespace Retort::Scripting {
    UIScriptObject::UIScriptObject(const std::shared_ptr<UI::UI> &ui, std::shared_ptr<Runtime> runtime)
        : ScriptObjectWrapper("__ui", ui)
        , _runtime(runtime)
        , _references(std::map<std::string, Runtime::Reference>())
    { }

    Feedback UIScriptObject::consume(const UIEvent &event) {
        auto ref = _references.at(event.name);
        switch (event.control) {
        case UIEvent::GridControl:
            switch (event.gridControlEvent.type) {
            case (GridControlEvent::CellClick):
                _runtime->invokeMethod(ref, "cellClick", event.gridControlEvent.cellClickX, event.gridControlEvent.cellClickY);
                break;
            default: crash("Unknown GridControl event");
            }
            break;
        default: crash("Unknown UI event from %s", event.name.c_str())
        }
        return Feedback::Continue;
    }

    Feedback UIScriptObject::frameEnded() {
        return Feedback::Continue;
    }

    void UIScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime) {
        runtime->assign("newGrid", this, [](lua_State *L) -> int {
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            auto name = lua_tostring(L, 1);
            closure.runtime->push(std::make_shared<GridControlScriptObject>(name));
            return 1;
        });
        runtime->assign("controls", Runtime::EmptyTable);
        runtime->assign("show", this, [](lua_State *L) -> int {
            auto closure = Runtime::unpackClosure<UIScriptObject>(L);
            auto obj = Runtime::unpackUserdata<GridControlScriptObject>(L, 1); // TODO: ControlScriptObject
            lua_getfield(L, 1, "events");
            auto ref = Runtime::createReference(L);
            closure.that->addReference(obj->getObject()->getName(), ref);
            closure.that->getObject()->show(obj->getObject());
            return 0;
        });
    }

    void UIScriptObject::addReference(const std::string & name, Runtime::Reference ref) {
        _references.insert(std::make_pair(name, ref));
    }
}
