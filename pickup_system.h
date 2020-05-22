#ifndef PICKUP_SYSTEM_H_
#define PICKUP_SYSTEM_H_

#include <memory>
#include <iostream>

#include "component_manager.h"
#include "type_id.h"
#include "physics_component.h"
#include "time_component.h"
#include "system.h"

enum PickupType
{
    PICKUPPER,
    PICKUPPEE
};

class CompPickupper : public Component
{
    void set_type() override { _type = type_id<CompPickupper>; }
};

class CompPickupee : public Component
{
    void set_type() override { _type = type_id<CompPickupee>; }
};

class SysPickup: public System
{
public:
    SysPickup()
    {
        _type = type_id<CompPickupper>;
        _type_name = "pickup";
    }

    void update(double dt) override
    {
        std::vector<CompPickupper>& pickupper_vec = get_array<CompPickupper>();
        std::vector<CompPickupee>& pickupee_vec = get_array<CompPickupee>();
        assert(pickupper_vec.size());
        double current_time = pickupper_vec[0].sibling<CompTime>()->current_time; 
        for (auto it = pickupper_vec.begin(); it != pickupper_vec.end(); ++it)
        {
            glm::vec3& pos = (*it).sibling<CompPosition>()->pos;
            for (auto it2 = pickupee_vec.begin(); it2 != pickupee_vec.end(); ++it2)
            {
                glm::vec3& pos2 = (*it2).sibling<CompPosition>()->pos;
                if (glm::length(pos - pos2) < 2)
                {
                    std::cout << "PICKED UP" << "\n";
                }
            }
        }
    }

};

#endif  // PICKUP_SYSTEM_H_
