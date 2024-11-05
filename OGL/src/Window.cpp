#include "Window.h"
#include <iostream>


Window::Window(int width, int height, const std::string& title)
    : width(width), height(height), title(title), window(nullptr) {}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::Initialize() {
	// initilizing library
	if (!glfwInit())
	{
		false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);


    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSwapInterval(1); // Enable vsync
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window);
}



GLFWwindow* Window::GetGLFWwindow() const {
    return window;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
