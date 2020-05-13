#ifndef PHYSICS_SYSTEM_H_
#define PHYSICS_SYSTEM_H_

#include <memory>
#include <iostream>

#include "component_manager.h"
#include "type_id.h"
#include "physics_component.h"
#include "time_component.h"
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
        std::vector<CompPhysics>& phys_vec = 
            std::dynamic_pointer_cast<ComponentArray<CompPhysics>>(in_array)->_array;
        assert(phys_vec.size());
        double current_time = phys_vec[0].sibling<CompTime>()->current_time; 
        for (auto it = phys_vec.begin(); it != phys_vec.end(); ++it)
        {
            CompPosition * pos_comp = (*it).sibling<CompPosition>();
            pos_comp->pos.y = pos_comp->pos.y + (*it).vel.y*dt;
            (*it).vel.y = (*it).vel.y + 9.8*dt;
            std::cout << "POS: " << (*it).vel.y << "\n";
        }
    }

    CompType get_type() const
    {
        return _type;
    }
};

#endif  // PHYSICS_SYSTEM_H_
