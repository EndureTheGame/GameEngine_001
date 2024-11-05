#pragma once

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void Initialize();
    void PollEvents();
    void SwapBuffers();
    bool ShouldClose() const;

    GLFWwindow* GetGLFWwindow() const;

private:
    GLFWwindow* window;
    int width, height;
    std::string title;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};