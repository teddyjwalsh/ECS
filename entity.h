#ifndef ENTITY_H_
#define ENTITY_H_

#include "component.h"

class Entity
{
public:
    std::map<CompType, std::vector<CompIndex>> _components;
};

#endif  // ENTITY_H_
