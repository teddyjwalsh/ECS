#ifndef ENTITY_H_
#define ENTITY_H_

#include <map>

#include "component.h"

class Entity
{

public:
    std::map<CompType, CompIndex> _components;
    static std::vector<CompType> makeup;
};

#endif  // ENTITY_H_
