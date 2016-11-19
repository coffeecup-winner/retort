#include "GridControlScriptObject.h"

Retort::Scripting::GridControlScriptObject::GridControlScriptObject(const std::string &name, std::shared_ptr<Reference> data)
    : ScriptObjectWrapper("__grid", std::make_shared<GridControl>(name, data))
{ }

void Retort::Scripting::GridControlScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime) {
    runtime->assign("events", [](std::shared_ptr<Runtime> table) -> void {
        table->assign("cellClick", Runtime::EmptyFunction);
    });
}
