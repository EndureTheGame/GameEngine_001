#ifndef INPUT_H
#define INPUT_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Camera.h"


class Input {
public:
    static void Initialize(GLFWwindow* window);
    static void ProcessInput(GLFWwindow* window, Camera& camera, float deltaTime);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void ErrorCallback(int error, const char* description);

private:
    static GLFWwindow* window;
    static bool firstMouse;
    static float lastX, lastY;
    static Camera camera;
};

#endif // INPUT_H
