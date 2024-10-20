#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "glad/glad.h"
#include "SDL.h"

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

    void activate(GLuint unit);
    void bind() const;
    void activateAndBind(GLuint unit);
    void unbind();
    void deleteShader();

    GLuint getID() const { return textureID; }
    const std::string& getType() { return  type; }
    const std::string& getPath() { return filePath; }

    void setType(const std::string& type) { this->type = type; }

private:
    void loadTexture(const std::string& path);

    int texWidth, texHeight, texChannels;
    GLuint textureID = 0;
    std::string filePath;
    std::string type;
};



#endif //TEXTURE_H
