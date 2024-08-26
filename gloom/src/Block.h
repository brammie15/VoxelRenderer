//
// Created by Bram on 26/08/2024.
//

#ifndef GLOOM_BLOCK_H
#define GLOOM_BLOCK_H

//This will hold all the data of a block, but not the mesh since this is held by the chunk


#include "BlockType.h"


class Block {
public:
    Block(BlockType type) : m_type(type) {}

    BlockType getType() const { return m_type; }


private:
    BlockType m_type;
};


#endif //GLOOM_BLOCK_H
