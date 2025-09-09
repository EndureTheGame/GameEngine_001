#include "LightNode.h"

LightNode::LightNode(LightSource* light)
    : m_Light(light) {
}

void LightNode::Update(float dt)
{
    // Optional: animate light position or properties
    // Example: oscillate light position
    static float time = 0.0f;
    time += dt;
    glm::vec3 animatedPos = glm::vec3(sin(time) * 5.0f, 10.0f, cos(time) * 5.0f);
    m_Light->SetPosition(animatedPos);

    SceneNode::Update(dt);
}

void LightNode::Draw(const glm::mat4& parentTransform,
    const glm::mat4& viewMatrix,
    const glm::mat4& projMatrix)
{
    // Optional: pass light uniforms to shader here if needed
    SceneNode::Draw(parentTransform * GetTransform(), viewMatrix, projMatrix);
}
