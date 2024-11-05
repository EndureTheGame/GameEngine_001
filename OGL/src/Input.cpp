#include "Input.h"
#include <iostream>

GLFWwindow* Input::window = nullptr;
bool Input::firstMouse = true;
float Input::lastX = 0.0f;
float Input::lastY = 0.0f;
Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));
glm::vec3 cameraPos = glm::vec3(0.0f, 50.0f, 50.0f);

void Input::Initialize(GLFWwindow* window) {
    Input::window = window;
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetErrorCallback(ErrorCallback);
}

void Input::ProcessInput(GLFWwindow* window, Camera& camera, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
        std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void Input::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Input::ErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
