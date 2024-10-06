#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    unsigned int VAO;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

    void render();
    void cleanup();

private:
    GLuint VBO, EBO;

    void setupMesh();
};



#endif //MESH_H
