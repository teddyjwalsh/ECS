#ifndef ACTION_SYSTEM_H_
#define ACTION_SYSTEM_H_

#include <memory>
#include <iostream>

#include "component_manager.h"
#include "type_id.h"
#include "physics_component.h"
#include "time_component.h"
#include "system.h"

#define MAX_SPEED 10


class SysAction: public System
{
public:
    SysAction()
    {
         _type = type_id<CompPlayer>;
        _type_name = "action";
    }

    void update(double dt) override
    {
        std::vector<CompPlayer>& player_vec = get_array<CompPlayer>();
        assert(player_vec.size());
        auto& player = player_vec[0];
        auto key_state = player.sibling<CompKeyState>();
        auto& cam = player.sibling<CompCamera>()->camera;
        auto physics = player.sibling<CompPhysics>();
        auto graphics = player.sibling<CompGraphics>();
        double current_time = player_vec[0].sibling<CompTime>()->current_time; 

        // Camera movement
        int width, height;
        graphics->get_window_size(width, height);
        glm::vec3 fv = cam.get_forward_vector();
        glm::vec3 rv = cam.get_right_vector();
        glm::vec3 uv = cam.get_up_vector();
        fv = glm::normalize( fv + 1.8f*float((key_state->mouse_pos_x - width / 2) / width)*rv - 0.9f*float((key_state->mouse_pos_y - height / 2) / height) * uv);
        cam.set_forward_vector(fv);

        // WASD Movement
        if (key_state->pressed[GLFW_KEY_W])
        {
            fv = cam.get_forward_vector(); 
            fv = glm::normalize(glm::vec3(fv.x, 0, fv.z));
            //glm::vec3 vel_component = glm::vec3(fv)*glm::dot(physics->vel, fv);
            physics->vel.x = 0;
            physics->vel.z = 0;
            physics->vel += fv*MAX_SPEED;
        }
        else
        {
            physics->vel.x = 0;
            physics->vel.z = 0;
        }
    }

};

#endif  // ACTION_SYSTEM_H_
