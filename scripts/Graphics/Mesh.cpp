#include "Mesh.h"
#include <iostream>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
    :vertices(vertices), indices(indices){
        setupMesh();
}

void Mesh::calculateAvgNormals(std::vector<Vertex>& vertices, const std::vector<GLuint>& indices){
    // Initialize all vertex normals to zero
    for (auto& vertex : vertices) {
        vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // Loop through all the triangles (indices should be a multiple of 3)
    for (size_t i = 0; i < indices.size(); i += 3) {
        // Get the vertices of the current triangle
        Vertex& v0 = vertices[indices[i]];
        Vertex& v1 = vertices[indices[i + 1]];
        Vertex& v2 = vertices[indices[i + 2]];

        // Calculate the face normal for this triangle
        glm::vec3 faceNormal = calculateFaceNormal(v0, v1, v2);

        // Accumulate the face normal into each vertex's normal
        v0.normal += faceNormal;
        v1.normal += faceNormal;
        v2.normal += faceNormal;
    }

    // Normalize all the accumulated normals to get the average normal
    for (auto& vertex : vertices) {
        vertex.normal = glm::normalize(vertex.normal);
    }
}

glm::vec3 Mesh::calculateFaceNormal(const Vertex& v0, const Vertex& v1, const Vertex& v2){
    // Compute the edges of the triangle
    glm::vec3 edge1 = v1.position - v0.position;
    glm::vec3 edge2 = v2.position - v0.position;

    // Compute the cross product of the two edges
    glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

    return normal;
}


void Mesh::setupMesh() {
    //generate the buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    //texCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1);

    //normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLuint>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}




