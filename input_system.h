#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

//#include "GLFW/glfw3.h"
#include "system.h"
#include "keystate_component.h"
#include "graphics_component.h"

class SysInput : public System
{
public:
    void update(double dt) override
    {
        auto& key_state = get_array<CompKeyState>()[0];
        auto& graphics_comp = get_array<CompGraphics>()[0];
        for (auto& k : key_state.pressed)
        {
            auto key = k.first;
            //k.second[key] = glfwGetKey(graphics_comp.window, key);
        }
    }
};

#endif  // INPUT_SYSTEM_H_
