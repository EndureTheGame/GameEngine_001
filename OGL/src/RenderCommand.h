#pragma once
#include <glad.h>
#include <cstdint>
#include <glm/ext/vector_float4.hpp>
#include "VertexArray.h"
#include "ElementBuffer.h"

struct RenderCommand
{
    static void Init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    static void SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    static void Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static void DrawIndexed(const VertexArray& vao, const ElementBuffer& ebo)
    {
        vao.Bind();
        ebo.Bind();
        glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
    }
};
