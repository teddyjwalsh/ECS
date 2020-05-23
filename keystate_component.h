#ifndef KEYSTATE_COMPONENT_H_
#define KEYSTATE_COMPONENT_H_

#include <unordered_map>
#include "glfw_defines.h"

#include "component.h"

class CompKeyState : public Component
{
public:
    CompKeyState()
    {
        std::vector<int> keys_to_use = {
                            GLFW_KEY_W,
                            GLFW_KEY_A,
                            GLFW_KEY_S,
                            GLFW_KEY_D,
                            GLFW_KEY_SPACE,
                            0,
                            1,
                        };
        for (auto it : keys_to_use)
        {
            pressed[it] = false;
            push[it] = false;
            release[it] = false;
            held[it] = false;
        }
    }
    std::unordered_map<int, bool> pressed;
    std::unordered_map<int, double> pressed_time;
    std::unordered_map<int, bool> push;
    std::unordered_map<int, bool> release;
    std::unordered_map<int, bool> held;
    double mouse_pos_x;
    double mouse_pos_y;
};

#endif  // KEYSTATE_COMPONENT_H_
