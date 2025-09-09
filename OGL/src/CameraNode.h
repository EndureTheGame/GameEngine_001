#pragma once
#include "SceneNode.h"
#include "Camera.h"

class CameraNode : public SceneNode
{
public:
    CameraNode(Camera* camera);
    void Update(float dt) override;
    void Draw(const glm::mat4& parentTransform,
        const glm::mat4& viewMatrix,
        const glm::mat4& projMatrix) override;

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

private:
    Camera* m_Camera;
};
