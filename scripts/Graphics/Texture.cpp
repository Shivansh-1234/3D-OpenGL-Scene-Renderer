#include "Texture.h"
#include <iostream>
#include "SDL_image.h"


Texture::Texture(const std::string &path)
    :texWidth(0), texHeight(0), texChannels(0), filePath(path) {
    loadTexture(path);
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

void Texture::loadTexture(const std::string &path) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if(surface) {
        std::cout << "Surface : " << path << " Loaded successfully :)\n";
    }
    else {
        std::cerr << " Unable to load surface : " << path << " because : " << IMG_GetError() << std::endl;
        return;
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
        break;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format,
        GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

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
    glDeleteTextures(1, &textureID);
}


