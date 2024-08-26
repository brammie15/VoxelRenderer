//
// Created by Bram on 25/08/2024.
//

#include "TextureManager.h"

Texture * TextureManager::getTexture(const std::string &path) {
    if (m_textures.find(path) == m_textures.end()) {
        m_textures[path] = new Texture(path);
    }
    return m_textures[path];
}
