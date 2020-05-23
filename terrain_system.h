#ifndef TERRAIN_SYSTEM_H_
#define TERRAIN_SYSTEM_H_

#include "system.h"
#include "player_components.h"
#include "camera_component.h"
#include "chunk_components.h"
#include "generation/island.h"

#define CHUNK_SIZE_X 128
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 20
#define MAP_SIZE_Z 10

class SysTerrain : public System
{
public:
    SysTerrain():
        island(1)
    {
        _type_name = "terrain";
    }

    void update(double dt) override 
    {
        auto& players = get_array<CompPlayer>(); 
        auto& player1 = players[0]; 
        auto cam1 = player1.sibling<CompCamera>(); 
        auto pos1 = player1.sibling<CompPosition>(); 
        auto& loaded_chunks = get_array<CompLoadedChunks>()[0]; 
        auto& chunk_data_queue = get_array<CompChunkDataQueue>()[0]; 
        ChunkCoord highest_priority_chunk = get_chunk_to_load(pos1->pos, cam1->view);
        ChunkData new_chunk = island.get_chunk(highest_priority_chunk.x, 
                                               highest_priority_chunk.y,
                                               highest_priority_chunk.z,
                                               CHUNK_SIZE_X,
                                               CHUNK_SIZE_Y,
                                               CHUNK_SIZE_Z);
        loaded_chunks.chunks.insert(highest_priority_chunk);
        chunk_data_queue.chunks.push_back(new_chunk);

        for (auto& p : players)
        {
            SLOG_DEBUG("Setting player terrain {}");
            auto player_terrain = p.sibling<CompPlayerTerrain>();
            if (player_terrain != nullptr)
            {
                auto player_bounds = p.sibling<CompBounds>();
                auto player_pos = p.sibling<CompPosition>();
                player_terrain->blocks.clear();
                set_player_terrain(player_terrain, player_pos, player_bounds);
            }
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
        glm::ivec3 start_block = glm::floor(player_pos->pos - player_bounds->bounds/2.0);
        glm::ivec3 end_block = glm::floor(player_pos->pos + player_bounds->bounds/2.0) + glm::vec3(1,1,1);
        glm::ivec3 block_size = end_block - start_block;
        std::vector<BlockType> blocks = island.get_chunk(start_block.x, start_block.y, start_block.z,
                                                         block_size.x, block_size.y, block_size.z); 
        SLOG_DEBUG("Start block {} {} {}", start_block.x, start_block.y, start_block.z);
        SLOG_DEBUG("End block {} {} {}", end_block.x, end_block.y, end_block.z);
        
        
        for (int i = start_block.z; i < end_block.z; ++i)
        {
            for (int j = start_block.y; j < end_block.y; ++j)
            {
                for (int k = start_block.x; k < end_block.x; ++k)
                {
                    BlockType block_type = blocks[(k-start_block.x) + 
                        block_size.x*(j-start_block.y) + 
                        block_size.x*block_size.y*(i-start_block.z)];
                    if (block_type > 0)
                    {
                        SLOG_DEBUG("Player terrain block : {} {} {}", i, j, k);
                        player_terrain->blocks[glm::vec3(i,j,k)] = block_type;
                    }
                }
            }
        }
        
    }


private:
    generation::Island island;

};

#endif  // TERRAIN_SYSTEM_H_
