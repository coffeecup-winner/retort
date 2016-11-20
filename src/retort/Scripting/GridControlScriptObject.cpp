#include "GridControlScriptObject.h"

Retort::Scripting::GridControlScriptObject::GridControlScriptObject(const std::string &name, std::shared_ptr<Reference> control)
    : ScriptObjectWrapper("__grid", std::make_shared<GridControl>(name, control))
{ }

void Retort::Scripting::GridControlScriptObject::fillMetaTable(std::shared_ptr<Runtime> runtime) { }
