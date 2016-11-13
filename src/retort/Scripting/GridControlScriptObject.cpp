#include "GridControlScriptObject.h"

Retort::Scripting::GridControlScriptObject::GridControlScriptObject(const std::string &name)
    : ScriptObjectWrapper("__grid", std::make_shared<GridControl>(name))
{ }

void Retort::Scripting::GridControlScriptObject::fillMetaTable(std::shared_ptr<Runtime> state) { }
