#include "CameraNode.h"

CameraNode::CameraNode(Camera* camera)
    : m_Camera(camera) {
}

void CameraNode::Update(float dt)
{
    // Optional: animate camera or respond to input
    SceneNode::Update(dt);
}

void CameraNode::Draw(const glm::mat4& parentTransform,
    const glm::mat4& viewMatrix,
    const glm::mat4& projMatrix)
{
    // Camera doesn't draw anything, but you could visualize it if needed
    SceneNode::Draw(parentTransform * GetTransform(), viewMatrix, projMatrix);
}

glm::mat4 CameraNode::GetViewMatrix() const
{
    return m_Camera->GetViewMatrix();
}

glm::mat4 CameraNode::GetProjectionMatrix() const
{
    return m_Camera->GetProjectionMatrix();
}
