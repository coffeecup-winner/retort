#pragma once

#include <string>

#include <lua.hpp>

#include <Scripting/Runtime.h>

namespace Retort::Scripting {
    class Runtime;

    class ScriptObject {
        std::string _name;

    protected:
        explicit ScriptObject(const std::string &name);

    public:
        virtual ~ScriptObject();
        virtual void fillMetaTable(std::shared_ptr<Runtime> state) = 0;

        const std::string &getMetaTableName() const;
    };
}
