#ifndef MESH_H
#define MESH_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Texture.h"

class Shader;

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures {};

    unsigned int VAO;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices,
        const std::vector<Texture>& textures);

    static void calculateAvgNormals(std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

    void render(const std::shared_ptr<Shader>& shader);
    void cleanup();

private:
    GLuint VBO, EBO;

    void setupMesh();
    static glm::vec3 calculateFaceNormal(const Vertex& v0, const Vertex& v1, const Vertex& v2);
};



#endif //MESH_H
