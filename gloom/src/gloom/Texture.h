//
// Created by Bram on 23/08/2024.
//

#ifndef GLOOM_TEXTURE_H
#define GLOOM_TEXTURE_H


#include <string>

class Texture {
public:
    Texture(const std::string& filename);

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    unsigned int getTexture() const { return m_texture; }
private:
    unsigned int m_texture{ 0 };
};


#endif //GLOOM_TEXTURE_H
