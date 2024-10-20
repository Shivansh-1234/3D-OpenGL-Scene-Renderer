#ifndef MODEL_H
#define MODEL_H


#include <vector>
#include <string>
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>


class Mesh;
class Shader;
class Texture;

class Model {
public:
    Model(const std::string& path);

    void render(const std::shared_ptr<Shader>& shader);

private:
    std::vector<Mesh> meshes;
    std::string directory;

    std::vector<Texture> loadedTextures;

    void loadModel(const std::string& path);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};



#endif //MODEL_H
