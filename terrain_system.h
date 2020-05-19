#ifndef TERRAIN_SYSTEM_H_
#define TERRAIN_SYSTEM_H_

class SysTerrain : public System
{
    void update(double dt) 
    {
        auto& player1 = get_array<CompPlayer>()[0]; 
        auto& cam1 = player1.sibling<CompCamera>(); 
        auto& pos1 = player1.sibling<CompPosition>(); 
        auto& loaded_chunks = get_array<CompLoadedChunks>()[0]; 
        auto& chunk_data_queue = get_array<CompChunkDataQueue>()[0]; 
        ChunkCoord highest_priority_chunk = get_chunk_to_load(pos1, cam1);
        ChunkData new_chunk = island.get_chunk(highest_priority_chunk);
        loaded_chunks.add_chunk(highest_priority_chunk);
        chunk_data_queue.push_back(new_chunk);
    }
};

#endif  // TERRAIN_SYSTEM_H_
