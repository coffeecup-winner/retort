#pragma once
#include <common.h>

#include <Scripting/ScriptObject.h>

namespace Retort::Scripting {
    template <typename Object>
    class ScriptObjectWrapper : public ScriptObject {
        NONCOPYABLE(ScriptObjectWrapper)

        std::shared_ptr<Object> _object;

    public:
        ScriptObjectWrapper(const std::string &name, const std::shared_ptr<Object> &object);
        std::shared_ptr<Object> getObject() const;
        virtual void fillMetaTable(std::shared_ptr<Runtime> runtime) = 0;
    };

    template<typename Object>
    inline ScriptObjectWrapper<Object>::ScriptObjectWrapper(const std::string & name, const std::shared_ptr<Object> &object)
        : ScriptObject(name)
        , _object(object)
    { }

    template<typename Object>
    inline std::shared_ptr<Object> ScriptObjectWrapper<Object>::getObject() const {
        return _object;
    }
}
