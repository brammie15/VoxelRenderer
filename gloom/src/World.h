//
// Created by Bram on 26/08/2024.
//

#ifndef GLOOM_WORLD_H
#define GLOOM_WORLD_H

#include <vector>
#include "Chunk.h"
#include "gloom/Singleton.h"


class World: public Singleton<World> {
public:
    World();
    Chunk * getChunk(int x, int z);
    void generateChunk(int x, int z);

    //Optional ig
    Block* getBlock(int x, int y, int z);
    void setBlock(int x, int y, int z, const Block& block);

    void Draw(GLuint shaderProgram, glm::vec3 playerPos);

    ChunkLoadStatus isChunkGenerated(int x, int z) {
        //if out of bounds, return true
        if (x < 0 || x >= WORLD_WIDTH || z < 0 || z >= WORLD_HEIGHT) {
            return ChunkLoadStatus::NOT_AVAILABLE;
        } else {
            return chunkGenerated[x][z];
        }
    }

private:
    //2D  array
    Chunk* chunks[WORLD_HEIGHT][WORLD_WIDTH]{ nullptr };
    ChunkLoadStatus chunkGenerated[WORLD_HEIGHT][WORLD_WIDTH]{ ChunkLoadStatus::NOT_GENERATED };

};


#endif //GLOOM_WORLD_H
