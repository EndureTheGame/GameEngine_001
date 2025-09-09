#pragma once
#include "SceneNode.h"
#include "LightSource.h"

class LightNode : public SceneNode
{
public:
    LightNode(LightSource* light);
    void Update(float dt) override;
    void Draw(const glm::mat4& parentTransform,
        const glm::mat4& viewMatrix,
        const glm::mat4& projMatrix) override;

private:
    LightSource* m_Light;
};
