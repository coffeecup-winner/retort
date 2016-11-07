#pragma once

#include <Scripting/Runtime.h>
#include <Scripting/ScriptObject.h>

namespace Retort::Scripting {
    class UIScriptObject : public ScriptObject {
    public:
        UIScriptObject();
        void fillMetaTable(std::shared_ptr<Runtime> state) override;
    };
}
