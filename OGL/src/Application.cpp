#include "Application.h"


Application::Application(int width, int height, const std::string& title)
    : window(width, height, title), shader("BasicShader.shader"), camera(glm::vec3(0.0f, 0.0f, -3.0f)) {}
void Application::Initialize() {
    window.Initialize();
    input.Initialize(window.GetGLFWwindow());
    // Initialize other components (e.g., VAO, EBO, Shader)
}


void Application::Run() {
    Initialize();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!window.ShouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.PollEvents();
        input.ProcessInput(window.GetGLFWwindow(), camera, deltaTime);
        renderer.Clear();

        // Render your objects
        Render();

        window.SwapBuffers();
    }
}

void Application::Render() {
    renderer.Draw(vao, ebo, shader);
}
