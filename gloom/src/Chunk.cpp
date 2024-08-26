//
// Created by Bram on 25/08/2024.
//

#include "Chunk.h"
#include "gloom/Mesh.h"
#include "Cube.h"
#include "gloom/Singleton.h"

#include <vector>
#include "World.h"


void Chunk::loadBlocks() {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                glm::vec3 actualPos = glm::vec3(x, y, z) + glm::vec3(m_chunkPos.x * CHUNK_SIZE, 0, m_chunkPos.y * CHUNK_SIZE);
                BlockType blockType = generateTerrain(actualPos);
                if (m_blocks[x][y][z] != nullptr) {
                    delete m_blocks[x][y][z];
                }
                m_blocks[x][y][z] = new Block(blockType);
            }
        }
    }

}

void Chunk::loadMesh() {
    std::vector<Mesh::Vertex> vertexes{};
    std::vector<unsigned int> indices{};

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                //Check direction and call LoadFace on that direction
                Block* block = this->getBlock(x, y, z);
                if (block->getType() != BlockType::AIR) {
                    BlockType type = block->getType();
                    //Get the block in world space using World::GetInstance().getBlock
                    Block* leftBlock = World::GetInstance().getBlock(x - 1 + m_chunkPos.x * CHUNK_SIZE, y, z  + m_chunkPos.y * CHUNK_SIZE);
                    Block* rightBlock = World::GetInstance().getBlock(x + 1 + m_chunkPos.x * CHUNK_SIZE, y, z + m_chunkPos.y * CHUNK_SIZE);
                    Block* bottomBlock = World::GetInstance().getBlock(x + m_chunkPos.x * CHUNK_SIZE, y - 1, z + m_chunkPos.y * CHUNK_SIZE);
                    Block* topBlock = World::GetInstance().getBlock(x + m_chunkPos.x * CHUNK_SIZE, y + 1, z + m_chunkPos.y * CHUNK_SIZE);
                    Block* backBlock = World::GetInstance().getBlock(x + m_chunkPos.x * CHUNK_SIZE, y, z - 1 + m_chunkPos.y * CHUNK_SIZE);
                    Block* frontBlock = World::GetInstance().getBlock(x + m_chunkPos.x * CHUNK_SIZE, y, z + 1 + m_chunkPos.y * CHUNK_SIZE);




                    if (leftBlock->getType() == BlockType::AIR) {
                        Cube::LoadFace(Face::LEFT, vertexes, indices, glm::vec3(x, y, z), type);
                    }
                    if (rightBlock->getType() == BlockType::AIR) {
                        Cube::LoadFace(Face::RIGHT, vertexes, indices, glm::vec3(x, y, z),type);
                    }
                    if (bottomBlock->getType() == BlockType::AIR) {
                        Cube::LoadFace(Face::BOTTOM, vertexes, indices, glm::vec3(x, y, z), type);
                    }
                    if (topBlock->getType() == BlockType::AIR) {
                        Cube::LoadFace(Face::TOP, vertexes, indices, glm::vec3(x, y, z), type);
                    }
                    if (backBlock->getType() == BlockType::AIR) {
                        Cube::LoadFace(Face::FRONT, vertexes, indices, glm::vec3(x, y, z), type);
                    }
                    if (frontBlock->getType() == BlockType::AIR) {
                        Cube::LoadFace(Face::BACK, vertexes, indices, glm::vec3(x, y, z), type);
                    }
                }
            }
        }
    }

    m_mesh = Mesh(vertexes, indices);
    m_mesh.setPosition(glm::vec3(m_chunkPos.x * CHUNK_SIZE, 0, m_chunkPos.y * CHUNK_SIZE));
    m_mesh.setupMesh();
}

Chunk::Chunk(const glm::vec2 &pos): m_chunkPos(pos) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                m_blocks[x][y][z] = new Block(BlockType::AIR);
            }
        }
    }
}

BlockType Chunk::generateTerrain(glm::vec3 position) {
    double noise = perlin.octave2D_01((position.x * 0.01), (position.z * 0.01), 4);
    noise = pow(noise, 3);
    int height = noise * 70;
    if (position.y > height) {
        return BlockType::AIR;
    }
    else if (position.y == height) {
        //snow
        int variance = ((float)rand() / RAND_MAX) * 7; //between 0-7
        if (position.y > 20 + variance)
            return BlockType::SNOW;	//snow
        return BlockType::GRASS;		//grass
    }
    else {
        return BlockType::DIRT;		//dirt
    }
}

Chunk::Chunk() {
//    m_chunkPos = glm::vec2(0, 0);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                m_blocks[x][y][z] = new Block(BlockType::AIR);
            }
        }
    }


}

Chunk::~Chunk() {
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int y = 0; y < CHUNK_HEIGHT; ++y) {
            for (int z = 0; z < CHUNK_SIZE; ++z) {
                delete m_blocks[x][y][z]; // Delete each dynamically allocated Block
                m_blocks[x][y][z] = nullptr; // Set the pointer to nullptr to avoid dangling references
            }
        }
    }
}


