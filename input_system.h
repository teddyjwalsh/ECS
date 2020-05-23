#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include "glfw_defines.h"
#include "system.h"
#include "keystate_component.h"
#include "graphics_component.h"

#define HOLD_TIME 0.3

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
#ifdef USE_GLFW
        glfwGetCursorPos(graphics_comp.window, &key_state.mouse_pos_x, &key_state.mouse_pos_y);
        int width, height;
        graphics_comp.get_window_size(width, height);
        set_cursor_pos(width / 2, height / 2, graphics_comp.window);
#endif  // USE_GLFW
        for (auto& k : key_state.pressed)
        {
            auto key = k.first;
            bool new_key_state = false;
#ifdef USE_GLFW
            if (key == GLFW_MOUSE_BUTTON_1 || key == GLFW_MOUSE_BUTTON_2)
            {
                new_key_state = glfwGetMouseButton(graphics_comp.window, key);
            }
            else
            {
                new_key_state = glfwGetKey(graphics_comp.window, key);
            }
#endif
            if (k.second == new_key_state)
            {
                key_state.pressed_time[key] += dt;
                key_state.push[key] = false;
                key_state.release[key] = false;
                if (key_state.pressed_time[key] >= HOLD_TIME)
                {
                    key_state.held[key] = true;
                }
            }
            else
            {
                key_state.pressed_time[key] = 0;
                key_state.held[key] = false;
                if (new_key_state == GLFW_PRESS)
                {
                    key_state.push[key] = true;
                }
                else
                {
                    key_state.release[key] = true;
                }
            }
            k.second = new_key_state;
            SLOG_DEBUG("{} {}", k.first, k.second);
        }
    }

    void set_cursor_enabled(bool cursor_enabled, GLFWwindow * window)
    {
#ifdef USE_GLFW
        if (cursor_enabled)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
#endif  // USE_GLFW
    }

    void set_cursor_pos(int in_x, int in_y, GLFWwindow * window)
    {
#ifdef USE_GLFW
        glfwSetCursorPos(window, in_x, in_y);
#endif  //USE_GLFW
    }
};

#endif  // INPUT_SYSTEM_H_
