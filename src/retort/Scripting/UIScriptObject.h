#pragma once
#include <common.h>

#include <map>

#include <Scripting/Reference.h>
#include <Scripting/Runtime.h>
#include <Scripting/ScriptObjectWrapper.h>
#include <UI/UI.h>
#include <Utilities/Consumer.h>

using namespace Retort::UI;

namespace Retort::Scripting {
    class UIScriptObject
        : public ScriptObjectWrapper<UI::UI>
        , public Consumer<UIEvent>
    {
        NONCOPYABLE(UIScriptObject)

        std::shared_ptr<Runtime> _runtime;
        std::map<std::string, std::shared_ptr<Reference>> _controls = {};

    public:
        UIScriptObject(const std::shared_ptr<UI::UI> &ui, std::shared_ptr<Runtime> runtime);
        Feedback consume(const UIEvent &event) override;
        Feedback frameEnded() override;
        void fillMetaTable(std::shared_ptr<Runtime> runtime) override;
        void addControl(const std::string &name, const std::shared_ptr<Reference> &ref);
    };
}
