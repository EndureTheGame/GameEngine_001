#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Renderer& renderer, Shader& shader) const;

private:
    VertexArray va;
    VertexBuffer vb;
    ElementBuffer ebo;

    void setupMesh();
};
