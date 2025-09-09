#pragma once
#include <memory>
#include "SceneNode.h"
#include "CameraNode.h"



class Scene
{
public:
    Scene(Camera* camera);
    void Update(float dt);
    void Render();

    std::shared_ptr<SceneNode> GetRoot() { return m_Root; }
    std::shared_ptr<CameraNode> m_CameraNode;

private:
    std::shared_ptr<SceneNode> m_Root;
};
