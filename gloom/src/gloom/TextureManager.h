//
// Created by Bram on 25/08/2024.
//

#ifndef GLOOM_TEXTUREMANAGER_H
#define GLOOM_TEXTUREMANAGER_H


#include <unordered_map>
#include "Singleton.h"
#include "Texture.h"
#include <string>

class TextureManager: public Singleton<TextureManager>{
public:
    TextureManager() = default;
    ~TextureManager() override = default;

    Texture * getTexture(const std::string& path);

private:
    std::unordered_map<std::string, Texture*> m_textures;

};


#endif //GLOOM_TEXTUREMANAGER_H
