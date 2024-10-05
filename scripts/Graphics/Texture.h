#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "glad/glad.h"
#include "SDL2/SDL.h"

class Texture {
public:

    enum FORMAT : int{
        R = GL_RED,
        RG = GL_RGB,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    Texture(const std::string& path);
    ~Texture();

    void bind(GLuint unit = 0) const;
    void unbind();
    void deleteShader();

    GLuint getID() const { return textureID; }

private:
    void loadTexture(const std::string& path);

    int texWidth, texHeight, texChannels;
    GLuint textureID = 0;
    std::string filePath;
};



#endif //TEXTURE_H
