#ifndef SYSTEM_INTERFACE_H_
#define SYSTEM_INTERFACE_H_

#include <functional>

#include "glm/glm.hpp"
#include "entity.h"

class SystemInterface
{
public:
    std::function<EntityId(std::string, glm::vec3)> add_entity_pos;
    std::function<EntityId(std::string)> add_entity;
    std::function<ComponentArrayBase*(CompType)> get_array_base;
};

#endif  // SYSTEM_INTERFACE_H_
