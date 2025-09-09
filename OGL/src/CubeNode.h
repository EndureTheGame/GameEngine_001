// CubeNode.h
#pragma once
#include "SceneNode.h"
#include "Cube.h"

class CubeNode : public SceneNode
{
public:
    CubeNode(Cube* cube);
    void Draw(const glm::mat4& parentTransform,
        const glm::mat4& viewMatrix,
        const glm::mat4& projMatrix);

private:
    Cube* m_Cube;
};
