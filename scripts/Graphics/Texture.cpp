#include "Texture.h"

#include <algorithm>
#include <iostream>
#include "SDL_image.h"

bool endsWith(const std::string &filePath, const std::string &extension) {
    std::string lowerFilePath = filePath;
    std::transform(lowerFilePath.begin(), lowerFilePath.end(), lowerFilePath.begin(), ::tolower);
    if (lowerFilePath.size() >= extension.size() &&
        lowerFilePath.compare(lowerFilePath.size() - extension.size(), extension.size(), extension) == 0) {
        return true;
        }
    return false;
}


Texture::Texture(const std::string &path)
    :texWidth(0), texHeight(0), texChannels(0), filePath(path) {
    loadTexture(path);
}

Texture::~Texture() {
}

void Texture::loadTexture(const std::string &path) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (surface) {
        std::cout << "Surface : " << path << " Loaded successfully :)\n";
    }
    else {
        std::cerr << "Unable to load surface : " << path << " because : " << IMG_GetError() << std::endl;
        return;
    }

    // Check the file extension
    if (endsWith(path, ".png")) {
        std::cout << "This is a PNG file\n";
    } else if (endsWith(path, ".jpg")) {
        std::cout << "This is a JPG file\n";
    } else {
        std::cout << "Unknown file type\n";
    }

    texWidth = surface->w;
    texHeight = surface->h;
    texChannels = surface->format->BytesPerPixel;

    GLenum format;
    switch (texChannels) {
        // case 1: format = Texture::R;
        // break;
        //case 2: m_format = Texture::RG;
        //    break;
        case 3:
            format = Texture::RGB;
            break;
        case 4:
            format = Texture::RGBA;
            break;
        default: {
            std::cerr << "File format is not supported\n";
            SDL_FreeSurface(surface);
            return;
        }
    }

    flipTextureVertically(surface);

    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format,
    GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    unbind();
    SDL_FreeSurface(surface);
}

void Texture::activate(GLuint unit){
    glActiveTexture(GL_TEXTURE0 + unit);
}


void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::activateAndBind(GLuint unit){
    activate(unit);
    bind();
}


void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::deleteShader() {
    unbind();
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0; // Avoid dangling pointer
    }
}

void Texture::flipTextureVertically(SDL_Surface* surface){
    int pitch = surface->pitch;  // The size of a row in bytes
    Uint8* temp = new Uint8[pitch];  // Temporary buffer for row swapping
    Uint8* pixels = (Uint8*)surface->pixels;

    for (int i = 0; i < surface->h / 2; ++i) {
        Uint8* row1 = pixels + i * pitch;
        Uint8* row2 = pixels + (surface->h - i - 1) * pitch;

        // Swap the rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }

    delete[] temp;
}



