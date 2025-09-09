// SceneNode.cpp
#include "SceneNode.h"
#include "CubeNode.h"

SceneNode::SceneNode()
    : m_LocalTransform(1.0f) {
}

void SceneNode::AddChild(std::shared_ptr<SceneNode> child)
{
    m_Children.push_back(child);
}

void SceneNode::SetTransform(const glm::mat4& transform)
{
    m_LocalTransform = transform;
}

const glm::mat4& SceneNode::GetTransform() const
{
    return m_LocalTransform;
}

void SceneNode::Update(float deltaTime)
{
    for (auto& child : m_Children)
        child->Update(deltaTime);
}

void SceneNode::Draw(const glm::mat4& parentTransform,
    const glm::mat4& viewMatrix,
    const glm::mat4& projMatrix)
{
    glm::mat4 worldTransform = parentTransform * m_LocalTransform;

    for (auto& child : m_Children)
        child->Draw(worldTransform, viewMatrix, projMatrix);
}
