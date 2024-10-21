#include "Model.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include <assimp/postprocess.h>
#include <glm/glm.hpp>

Model::Model(const std::string& path){
    loadModel(path);
}

void Model::render(const std::shared_ptr<Shader>& shader){
    for(unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].render(shader);
    }
}

void Model::loadModel(const std::string& path){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate
        | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName){
    std::vector<Texture> textures;

    for(GLuint i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i , &str);
        std::string texPath = directory + "/" + std::string(str.C_Str());
        bool skip = false; //skip loading texture if already loaded
        for(GLuint j = 0; j < loadedTextures.size(); j++){
            if(texPath == loadedTextures[j].getPath())
            {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {
            Texture texture(texPath);
            texture.setType(typeName);
            textures.push_back(texture);
            loadedTextures.push_back(texture);
            std::cout << "Loaded Texture ID: " << texture.getID() << " from path: " <<texture.getPath() << std::endl;

        }

    }

    return textures;
}

void Model::processNode(aiNode* node, const aiScene* scene){
    for(GLuint i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for(GLuint i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene){
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    //vertex ki processing
    for(GLuint i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        if(mesh->HasNormals()){
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        else{
            std::cout << "MESH : " << mesh->mName.C_Str() << " has no Normals" << std::endl;
        }

        if(mesh->mTextureCoords[0]) {
            glm::vec2 texCoords;
            texCoords.x = mesh->mTextureCoords[0][i].x;
            texCoords.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = texCoords;
        }
        else{
            vertex.texCoords = glm::vec2(0.f, 0.f);
        }

        vertices.push_back(vertex);
    }

    //indices ki processing
    for(GLuint i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    //mat processing
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadMaterialTextures(material,aiTextureType_DIFFUSE,
        "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material,aiTextureType_SPECULAR,
        "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT,
        "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT,
        "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


    return {vertices, indices, textures};
}


