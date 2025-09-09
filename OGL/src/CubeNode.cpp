// CubeNode.cpp
#include "CubeNode.h"
#include "Renderer.h"

CubeNode::CubeNode(Cube* cube)
    : m_Cube(cube) {
}

void CubeNode::Draw(const glm::mat4& parentTransform,
                    const glm::mat4& viewMatrix,
                    const glm::mat4& projMatrix)
{
    glm::mat4 worldTransform = parentTransform * m_Cube->GetTransform();

    if(m_Cube)
        m_Cube->Draw(worldTransform, viewMatrix, projMatrix);

    SceneNode::Draw(worldTransform, viewMatrix, projMatrix);
}
