#ifndef PLAYER_COMPONENTS_H_
#define PLAYER_COMPONENTS_H_

#include "component.h"
#include "terrain_types.h"

class CompPlayer : public Component
{
public:
    void set_type() override { _type = type_id<CompPlayer>; }
};

class CompPlayerTerrain : public Component
{
public:
    std::unordered_map<glm::vec3, BlockType> blocks;
    void set_type() override { _type = type_id<CompPlayerTerrain>; }
};

#endif  // PLAYER_COMPONENTS_H_
