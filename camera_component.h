#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_

#include "component.h"
#include "graphics/camera.h"

class CompCamera : public Component
{
public:
    graphics::Camera camera;
};

#endif  // CAMERA_COMPONENT_H_
