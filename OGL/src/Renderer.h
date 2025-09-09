#pragma once

#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "RenderCommand.h"

class Renderer
{
public:
    static void Init() { RenderCommand::Init(); }
    static void Clear() { RenderCommand::Clear(); }

    static void BeginScene(const glm::mat4& view, const glm::mat4& projection)
    {
        s_ViewMatrix = view;
        s_ProjectionMatrix = projection;
    }

    static void EndScene() { /* Optional batching or post-processing */ }

    static void Draw(const VertexArray& vao,
        const ElementBuffer& ebo,
        Shader& shader,
        const glm::mat4& model)
    {
        shader.Bind();
        shader.SetUniformMat4f("model", model);
        shader.SetUniformMat4f("view", s_ViewMatrix);
        shader.SetUniformMat4f("projection", s_ProjectionMatrix);
        RenderCommand::DrawIndexed(vao, ebo);
    }

private:
    static glm::mat4 s_ViewMatrix;
    static glm::mat4 s_ProjectionMatrix;
};
