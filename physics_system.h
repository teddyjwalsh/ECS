#ifndef PHYSICS_SYSTEM_H_
#define PHYSICS_SYSTEM_H_

#include <memory>

#include "component_array.h"
#include "type_id.h"
#include "physics_component.h"
#include "system.h"

class SysPhysics : public System
{
public:
    SysPhysics()
    {
        _type = type_id<CompPhysics>;
    }

    void update(std::shared_ptr<ComponentArrayBase> in_array, 
                double dt) override
    {
    }

    CompType get_type() const
    {
        return _type;
    }
};

#endif  // PHYSICS_SYSTEM_H_
