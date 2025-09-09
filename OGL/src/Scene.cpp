#include "Scene.h"
#include "Renderer.h"

Scene::Scene(Camera* camera)
    : m_Root(std::make_shared<SceneNode>())
{
    m_CameraNode = std::make_shared<CameraNode>(camera);
    m_Root->AddChild(m_CameraNode);
}



void Scene::Update(float dt)
{
    m_Root->Update(dt);
}

void Scene::Render()
{
    glm::mat4 view = m_CameraNode->GetViewMatrix();
    glm::mat4 proj = m_CameraNode->GetProjectionMatrix();
    Renderer::BeginScene(view, proj);
    m_Root->Draw(glm::mat4(1.0f), view, proj);
    Renderer::EndScene();
}
