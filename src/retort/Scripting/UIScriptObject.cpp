#include "UIScriptObject.h"

namespace Retort::Scripting {
    UIScriptObject::UIScriptObject()
        : ScriptObject("__ui")
    { }

    void UIScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime) { }
}
