#pragma once
#include <common.h>

#include <Scripting/Runtime.h>
#include <Scripting/ScriptObjectWrapper.h>
#include <UI/UI.h>

using namespace Retort::UI;

namespace Retort::Scripting {
    class UIScriptObject : public ScriptObjectWrapper<UI::UI> {
    public:
        UIScriptObject(const std::shared_ptr<UI::UI> &ui);
        void fillMetaTable(std::shared_ptr<Runtime> state) override;
    };
}
