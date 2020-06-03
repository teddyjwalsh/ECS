#ifndef ISLAND_COMPONENT_H_
#define ISLAND_COMPONENT_H_

#include "component.h"
#include "generation/island.h"

class CompIsland : public Component
{
public:
    generation::Island island;
    
private:
    void set_type() override { _type = type_id<CompIsland>; }
};

#endif  // ISLAND_COMPONENT_H_
