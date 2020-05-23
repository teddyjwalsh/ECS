#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include "glfw_defines.h"
#include "system.h"
#include "keystate_component.h"
#include "graphics_component.h"

class SysInput : public System
{
public:
    SysInput()
    {
        _type_name = "input";
    }

    void update(double dt) override
    {
        auto& key_state = get_array<CompKeyState>()[0];
        auto& graphics_comp = get_array<CompGraphics>()[0];
        for (auto& k : key_state.pressed)
        {
            auto key = k.first;
#ifdef USE_GLFW
            k.second = glfwGetKey(graphics_comp.window, key);
#endif
        }
    }
};

#endif  // INPUT_SYSTEM_H_
