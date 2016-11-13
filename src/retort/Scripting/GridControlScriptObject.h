#pragma once

#include <Scripting/ScriptObjectWrapper.h>
#include <UI/GridControl.h>

using namespace Retort::UI;

namespace Retort::Scripting {
    class GridControlScriptObject : public ScriptObjectWrapper<GridControl> {
    public:
        GridControlScriptObject(const std::string &name);
        void fillMetaTable(std::shared_ptr<Runtime> state) override;
    };
}
