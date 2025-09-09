// SceneNode.h
#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SceneNode
{
public:
    SceneNode();
    virtual ~SceneNode() = default;

    void AddChild(std::shared_ptr<SceneNode> child);
    void SetTransform(const glm::mat4& transform);
    const glm::mat4& GetTransform() const;

    virtual void Update(float deltaTime);
    virtual void Draw(const glm::mat4& parentTransform,
        const glm::mat4& viewMatrix,
        const glm::mat4& projMatrix);

    const std::vector<std::shared_ptr<SceneNode>>& GetChildren() const {
        return m_Children;
    }

protected:
    glm::mat4 m_LocalTransform;
    std::vector<std::shared_ptr<SceneNode>> m_Children;
};
