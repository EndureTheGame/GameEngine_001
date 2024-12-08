#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : vertices(vertices), indices(indices), textures(textures),
    vb(vertices.data(), vertices.size() * sizeof(Vertex)),
    ebo(indices.data(), indices.size() * sizeof(unsigned int))
{
    setupMesh();
}

void Mesh::setupMesh() {
    va.Bind();
    vb.Bind();
	ebo.Bind();

    VertexBufferLayout layout;
    layout.Push<float>(3); // Position
    layout.Push<float>(3); // Normal
    layout.Push<float>(2); // Texture coordinates
    va.addBuffer(vb, layout);

    va.Undbind();
    vb.Unbind();
    ebo.Unbind();
}

void Mesh::Draw(Renderer& renderer, Shader& shader) const {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Activate texture unit
        std::string number;
        std::string name = textures[i].m_TypeName;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "texture_specular") {
            number = std::to_string(specularNr++);
        }

        shader.Setuniform1i((name + number).c_str(), i);
        textures[i].Bind(i);
    }
    //va.Bind();
    //ebo.Bind();
    //renderer.Draw(va, ebo, shader);
    glActiveTexture(GL_TEXTURE0); // Reset to default texture unit
}
