#include "Model.h"
#include <glm/gtx/transform.hpp>

Model::Model(const std::string& path) : shader("Shaders/BasicShader.shader") {
    LoadModel(path);
}

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    //debugging: 
    if (scene->mNumMeshes == 0)
    {
        std::cout << "ERROR::ASSIMP::No meshes found in file" << std::endl;
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        if (!mesh)
        {
            std::cerr << "Invalid mesh pointer" << std::endl;
			return;
        }
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture(directory + '/' + str.C_Str(), typeName);
        textures.push_back(texture);
    }
    return textures;
}

void Model::Draw(const glm::mat4& proj, const glm::mat4& view, glm::vec3& cameraPos, Renderer& renderer)
{
    shader.Bind();
    shader.SetUniformMat4f("projection", proj);
    shader.SetUniformMat4f("view", view);

   
    for (auto& mesh : meshes) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Adjust position as needed
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // Adjust scale as needed
        shader.SetUniformMat4f("model", model);

        shader.Setuniform4f("directionalLight.direction", -0.2f, -1.0f, -0.3f, 0.0f);
        shader.Setuniform4f("directionalLight.ambient", 0.05f, 0.05f, 0.05f, 1.0f);
        shader.Setuniform4f("directionalLight.diffuse", 0.4f, 0.4f, 0.4f, 1.0f);
        shader.Setuniform4f("directionalLight.specular", 0.5f, 0.5f, 0.5f,1.0f);


        mesh.Draw(renderer, shader);
    }
}
