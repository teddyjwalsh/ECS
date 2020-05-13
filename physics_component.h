#ifndef PHYSICS_COMPONENT_H_
#define PHYSICS_COMPONENT_H_

#include "glm/glm.hpp"
#include "component.h"
#include "type_id.h"

class CompPosition : public Component
{
public: 
    using Component::Component;
    glm::vec3 pos;
private:
    void set_type() override { _type = type_id<CompPosition>; }
};

class CompBounds : public Component
{
public: 
    using Component::Component;
    glm::vec3 bounds;
private:
    void set_type() override { _type = type_id<CompBounds>; }
};

class CompPhysics : public Component
{
public: 
    using Component::Component;
    float mass;
    glm::vec3 vel;
private:
    void set_type() override { _type = type_id<CompPhysics>; }
};

#endif  // PHYSICS_COMPONENT_H_
