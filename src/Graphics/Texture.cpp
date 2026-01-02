#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "AtomEngine.hpp"

using namespace AtomEngine;

Texture::Texture(const std::string& path) : path(path), width(0), height(0), channels(0), data(nullptr) {}

bool Texture::Load()
{
    data = stbi_load(path.c_str(), &width, &height, &channels, 4); // Forzar RGBA
    if (!data) {
        AtomError("Error cargando textura: " + path);
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    data = nullptr;
    return true;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
}
