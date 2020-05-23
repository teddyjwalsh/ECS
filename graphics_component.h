#ifndef GRAPHICS_COMPONENT_H_
#define GRAPHICS_COMPONENT_H_

#include "glfw_defines.h"

class CompGraphics : public Component
{
public:
    GLFWwindow * window;

    void get_window_size(int& width, int& height)
    {
#ifdef USE_GLFW
        glfwGetWindowSize(window, &width, &height);
#endif  // USE_GLFW
    }
};

#endif  // GRAPHICS_COMPONENT_H_
