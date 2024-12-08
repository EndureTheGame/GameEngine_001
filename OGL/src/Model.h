#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Renderer.h"

class Model {
public:
    std::vector<Mesh> meshes;
    std::string directory;
    Shader shader;
    Model(const std::string& path);
    void Draw( const glm::mat4& proj, const glm::mat4& view, glm::vec3& cameraPos, Renderer& renderer);

private:
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};
