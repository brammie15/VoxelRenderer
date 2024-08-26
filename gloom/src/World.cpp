//
// Created by Bram on 26/08/2024.
//

#include "World.h"
#include <iostream>
Chunk * World::getChunk(int x, int z) {
    return chunks[x][z];
}

void World::generateChunk(int x, int z) {
    //Calc offset so there is a 1 block space between each chunk
//    glm::vec2 offset = glm::vec2(x * 2, z * 2);
    if(chunks[x][z] != nullptr){
        delete chunks[x][z];
    }

    chunks[x][z] = new Chunk(glm::vec2(x, z));
    chunkGenerated[x][z] = ChunkLoadStatus::GENERATING;
    chunks[x][z]->loadBlocks();
    chunks[x][z]->loadMesh();
    chunkGenerated[x][z] = ChunkLoadStatus::GENERATED;

    //Call the sourounding chunks to update their mesh
    if (x > 0) {
        if(chunkGenerated[x - 1][z] == ChunkLoadStatus::GENERATED)
            chunks[x - 1][z]->loadMesh();
    }
    if (x < WORLD_WIDTH - 1) {
        if(chunkGenerated[x + 1][z] == ChunkLoadStatus::GENERATED)
            chunks[x + 1][z]->loadMesh();
    }
    if (z > 0) {
        if(chunkGenerated[x][z - 1] == ChunkLoadStatus::GENERATED)
            chunks[x][z - 1]->loadMesh();
    }
    if (z < WORLD_HEIGHT - 1) {
        if(chunkGenerated[x][z + 1] == ChunkLoadStatus::GENERATED)
            chunks[x][z + 1]->loadMesh();
    }
}

Block* World::getBlock(int x, int y, int z) {
    int chunkX = x / CHUNK_SIZE;
    int chunkZ = z / CHUNK_SIZE;

    int blockX = x % CHUNK_SIZE;
    int blockZ = z % CHUNK_SIZE;

    Chunk* chunk = chunks[chunkX][chunkZ];
    ChunkLoadStatus status = isChunkGenerated(chunkX, chunkZ);

    // check if the chunk is generated
    switch(isChunkGenerated(chunkX, chunkZ)) {
        case ChunkLoadStatus::NOT_GENERATED:
//            generateChunk(chunkX, chunkZ);
            return new Block(BlockType::DIRT);
            break;
        case ChunkLoadStatus::NOT_AVAILABLE:
            return new Block(BlockType::AIR);
            break;
        case ChunkLoadStatus::GENERATING:
            //Prob current chunk is generating
            break;
        default:
            break;
    }

    return chunks[chunkX][chunkZ]->getBlock(blockX, y, blockZ);
}

void World::setBlock(int x, int y, int z, const Block &block) {
    int chunkX = x / CHUNK_SIZE;
    int chunkZ = z / CHUNK_SIZE;

    int blockX = x % CHUNK_SIZE;
    int blockZ = z % CHUNK_SIZE;

    chunks[chunkX][chunkZ]->setBlock(blockX, y, blockZ, block);
}

void World::Draw(GLuint shaderProgram, glm::vec3 playerPos) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_HEIGHT; z++) {
            //Check if the player is RENDERDISTANCE chunks away from the chunk
            if (glm::distance(playerPos, glm::vec3(x * CHUNK_SIZE, 0, z * CHUNK_SIZE)) > RENDER_DISTANCE * CHUNK_SIZE) {
                continue;
            }
            if (chunkGenerated[x][z] == ChunkLoadStatus::GENERATED) {
                chunks[x][z]->Draw(shaderProgram);
            }
        }
    }

}

World::World() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int z = 0; z < WORLD_HEIGHT; z++) {
            chunks[x][z] = nullptr;
            chunkGenerated[x][z] = ChunkLoadStatus::NOT_GENERATED;
        }
    }
}
