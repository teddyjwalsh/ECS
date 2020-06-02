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
    CompBounds():
        bounds(0.9,1.8,0.9) {}
    glm::vec3 bounds;
    bool on_ground;
private:
    void set_type() override { _type = type_id<CompBounds>; }
};

class CompPhysics : public Component
{
public: 
    using Component::Component;
    float mass;
    glm::vec3 vel;
    glm::vec3 move_vel;
private:
    void set_type() override { _type = type_id<CompPhysics>; }
};

#endif  // PHYSICS_COMPONENT_H_
