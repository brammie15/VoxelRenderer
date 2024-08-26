//
// Created by Bram on 25/08/2024.
//

#ifndef GLOOM_CHUNK_H
#define GLOOM_CHUNK_H

#include "gloom/config.hpp"
#include "gloom/Mesh.h"
#include "gloom/PerlinNoise.hpp"
#include "BlockType.h"
#include "Block.h"

enum class ChunkLoadStatus{
    GENERATED,
    GENERATING,
    NOT_GENERATED,
    NOT_AVAILABLE,
};

static const int BLOCK_TYPES_COUNT = 4;

class Chunk {
public:
    Chunk();
    Chunk(const glm::vec2& pos);

    ~Chunk();

    void loadBlocks();
    void loadMesh();

    void Draw(GLuint shaderProgram) {
        m_mesh.draw(shaderProgram);
    }

    Mesh m_mesh;

    BlockType generateTerrain(glm::vec3 position);

    Block* getBlock(int x, int y, int z) {
        //if out of bounds, return dirt
        if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
            return new Block(BlockType::AIR);
        } else {
            if(m_blocks[x][y][z] == nullptr) {
                return new Block(BlockType::AIR);
            } else {
               return m_blocks[x][y][z];
            }
        }
    }

    void setBlock(int x, int y, int z, const Block& block) {
        m_blocks[x][y][z] = new Block(block.getType());
    }



private:
    Block* m_blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]{ nullptr };

    glm::vec3 m_position;
    glm::vec2 m_chunkPos;

};


#endif //GLOOM_CHUNK_H
