#ifndef PHYSICS_COMPONENT_H_
#define PHYSICS_COMPONENT_H_

#include "glm/glm.hpp"
#include "component.h"


class CompPosition : public Component
{
public: 
    glm::vec3 pos;
};

class CompBounds : public Component
{
public: 
    glm::vec3 bounds;
};

class CompPhysics : public Component
{
public: 
    CompIndex pos;
    CompIndex bounds; 
    static CompType type;
};

#endif  // PHYSICS_COMPONENT_H_
