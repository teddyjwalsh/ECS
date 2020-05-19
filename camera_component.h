#ifndef CAMERA_COMPONENT_H_
#define CAMERA_COMPONENT_H_

#include "component.h"

class CompCamera : public Component
{
public:
    glm::mat4 view;
};

#endif  // CAMERA_COMPONENT_H_
