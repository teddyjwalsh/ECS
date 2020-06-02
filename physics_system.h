#ifndef PHYSICS_SYSTEM_H_
#define PHYSICS_SYSTEM_H_

#include <math.h>
#include <memory>
#include <iostream>
#include <glm/ext.hpp>

#include "component_manager.h"
#include "type_id.h"
#include "physics_component.h"
#include "player_components.h"
#include "client_component.h"
#include "time_component.h"
#include "system.h"


template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// The physics system is intended to simulate physics
// and collision between all entities with a physics
// Component. 
// It also currently is intended to apply player input
// to player entities
class SysPhysics : public System
{
public:
    SysPhysics()
    {
        _type = type_id<CompPhysics>;
        _type_name = "physics";
    }

    void update(double dt) override
    {
        std::vector<CompPhysics>& phys_vec = 
            get_array<CompPhysics>(); 
        std::vector<CompPosition>& pos_vec = 
            get_array<CompPosition>(); 
        assert(phys_vec.size());
        double current_time = phys_vec[0].sibling<CompTime>()->current_time; 
        EntityId my_player = phys_vec[0].sibling<CompClient>()->player_id; 

        // Iterate all physics component
        for (auto it = phys_vec.begin(); it != phys_vec.end(); ++it)
        {
            CompPosition * pos_comp = (*it).sibling<CompPosition>();
            CompBounds * bounds_comp = (*it).sibling<CompBounds>();
            CompPlayerTerrain* terrain_comp = (*it).sibling<CompPlayerTerrain>();

            // If physics object is current client's player
            // THIS SHOULDN'T BE! key application should be on server
            // and should apply to all players until client side prediction
            // is implemented
            (*it).vel.y = (*it).vel.y - 9.8*dt;
            if (terrain_comp != nullptr)// && my_player == terrain_comp->get_entity())
            {
                SLOG_DEBUG("Trying to move");
                std::vector<glm::vec3> kv;
                kv.reserve(terrain_comp->blocks.size());
                for (auto k : terrain_comp->blocks)
                {
                    SLOG_DEBUG("\tBlock {} {} {}", k.first.x, k.first.y, k.first.z);
                    kv.push_back(k.first + glm::vec3(0.5));
                }
                move(dt, pos_comp->pos, (*it).vel, bounds_comp->bounds, (*it).on_ground, kv); 
            }

            // Apply kinematics and gravity
            // pos_comp->pos.y = pos_comp->pos.y + (*it).vel.y*dt;
        }
    }

    void move(
              double time_delta,
              glm::vec3& pos,
              glm::vec3& vel,
              glm::vec3& bounds,
              bool& on_ground,
              std::vector<glm::vec3> in_blocks)
    {
        double block_height = 1.0;
        double block_width = 1.0;
        double block_depth = 1.0;
        pos.x += vel.x*time_delta;
        for (auto in_block : in_blocks)
        {
            double y_pen = -std::abs(pos.y - in_block.y) +
                           (bounds.y / 2.0 + block_height / 2.0);
            double x_pen = -std::abs(pos.x - in_block.x) +
                           (bounds.x / 2.0 + block_width / 2.0);
            double z_pen = -std::abs(pos.z - in_block.z) +
                           (bounds.z / 2.0 + block_depth / 2.0);
            if (y_pen > 0 && x_pen > 0 && z_pen > 0)
            {
                pos.x -= x_pen*sgn(vel.x)*1.01;
                vel.x = 0;
            }
        }

        pos.z += vel.z*time_delta;
        for (auto in_block : in_blocks)
        {
            double y_pen = -std::abs(pos.y - in_block.y) +
                           (bounds.y / 2.0 + block_height / 2.0);
            double x_pen = -std::abs(pos.x - in_block.x) +
                           (bounds.x / 2.0 + block_width / 2.0);
            double z_pen = -std::abs(pos.z - in_block.z) +
                           (bounds.z / 2.0 + block_depth / 2.0);
            if (y_pen > 0 && x_pen > 0 && z_pen > 0)
            {
                pos.z -= z_pen*sgn(vel.z)*1.01;
                vel.z = 0;
            }
        }

        pos.y += vel.y*time_delta;
        for (auto in_block : in_blocks)
        {
            double y_pen = -std::abs(pos.y - in_block.y) +
                           (bounds.y / 2.0 + block_height / 2.0);
            double x_pen = -std::abs(pos.x - in_block.x) +
                           (bounds.x / 2.0 + block_width / 2.0);
            double z_pen = -std::abs(pos.z - in_block.z) +
                           (bounds.z / 2.0 + block_depth / 2.0);
            if (y_pen > 0 && x_pen > 0 && z_pen > 0)
            {
                SLOG_DEBUG("Corrected Y collision {}, {}, {}, {}, {}", y_pen, pos.y, vel.y, sgn(vel.y), bounds.y);
                pos.y -= y_pen*sgn(vel.y)*1.01;
                SLOG_DEBUG("\t after: {}", pos.y);
                vel.y = 0;
                on_ground = true;
            }
        }
    }
};

#endif  // PHYSICS_SYSTEM_H_
