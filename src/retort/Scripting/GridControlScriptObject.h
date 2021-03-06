#pragma once
#include <common.h>

#include <Scripting/ScriptObjectWrapper.h>
#include <UI/GridControl.h>

using namespace Retort::UI;

namespace Retort::Scripting {
    class GridControlScriptObject : public ScriptObjectWrapper<GridControl> {
        NONCOPYABLE(GridControlScriptObject)

    public:
        GridControlScriptObject(const std::string &name, std::shared_ptr<Reference> control);
        void fillMetaTable(std::shared_ptr<Runtime> runtime) override;
    };
}
