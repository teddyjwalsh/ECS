#ifndef TERRAIN_SYSTEM_H_
#define TERRAIN_SYSTEM_H_

#include "player_components.h"
#include "camera_component.h"
#include "chunk_components.h"

class SysTerrain : public System
{
    void update(double dt) 
    {
        auto& players = get_array<CompPlayer>(); 
        auto& player1 = players[0]; 
        auto cam1 = player1.sibling<CompCamera>(); 
        auto pos1 = player1.sibling<CompPosition>(); 
        auto& loaded_chunks = get_array<CompLoadedChunks>()[0]; 
        auto& chunk_data_queue = get_array<CompChunkDataQueue>()[0]; 
        ChunkCoord highest_priority_chunk = get_chunk_to_load(pos1->pos, cam1->view);
        ChunkData new_chunk = island.get_chunk(highest_priority_chunk);
        loaded_chunks.chunks.insert(highest_priority_chunk);
        chunk_data_queue.chunks.push_back(new_chunk);

        for (auto& p : players)
        {
            auto player_terrain = p.sibling<CompPlayerTerrain>();
            auto player_bounds = p.sibling<CompBounds>();
            auto player_pos = p.sibling<CompPosition>();
            player_terrain->blocks.clear();
            set_player_terrain(player_terrain, player_pos, player_bounds);
        }
    }

    ChunkCoord get_chunk_to_load(glm::vec3 pos, glm::mat4 view)
    {
        return glm::vec3(0,0,0);
    }

    void set_player_terrain(CompPlayerTerrain * player_terrain,
                            CompPosition * player_pos,
                            CompBounds * player_bounds)
    {
    }

};

#endif  // TERRAIN_SYSTEM_H_
