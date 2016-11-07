#include "ScriptObject.h"

namespace Retort::Scripting {
    ScriptObject::ScriptObject(const std::string &name)
        : _name(name)
    { }

    ScriptObject::~ScriptObject() { }

    const std::string &ScriptObject::getMetaTableName() const
    {
        return _name;
    }
}
