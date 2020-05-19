#ifndef CHUNK_COMPONENTS_H_
#define CHUNK_COMPONENTS_H_

#include <set>
#include <vector>

#include "component.h"
#include "terrain_types.h"

typedef std::vector<BlockType> ChunkData;

class CompLoadedChunks : public Component
{
public:
    std::unordered_set<ChunkCoord> chunks; 
};

class CompChunkDataQueue : public Component 
{
public:
    std::deque<ChunkData> chunks;
};

#endif  // CHUNK_COMPONENTS_H_
