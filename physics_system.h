#ifndef PHYSICS_SYSTEM_H_
#define PHYSICS_SYSTEM_H_

#include <memory>
#include <iostream>
#include <glm/ext.hpp>

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

    void update(double dt) override
    {
        std::vector<CompPhysics>& phys_vec = 
            get_array<CompPhysics>(); 
        std::vector<CompPosition>& pos_vec = 
            get_array<CompPosition>(); 
        assert(phys_vec.size());
        double current_time = phys_vec[0].sibling<CompTime>()->current_time; 
        for (auto it = phys_vec.begin(); it != phys_vec.end(); ++it)
        {
            CompPosition * pos_comp = (*it).sibling<CompPosition>();
            CompBounds * bounds_comp = (*it).sibling<CompBounds>();
            pos_comp->pos.y = pos_comp->pos.y + (*it).vel.y*dt;
            (*it).vel.y = (*it).vel.y + 9.8*dt;

            std::cout << "Phys pos " << glm::to_string(pos_comp->pos) << "\n";
        }
    }
};

#endif  // PHYSICS_SYSTEM_H_
