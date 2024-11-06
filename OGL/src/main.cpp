#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad.h>

#include <iostream>
#include <String>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Camera.h"
#include "Cube.h"
#include "LightSource.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>




void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void glfw_error_callback(int error, const char* description);

const unsigned int HEIGHT = 1080;
const unsigned int WIDTH = 1920;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 cameraPos = glm::vec3(0.0f, 50.0f, 50.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


int main(void)
{
	GLFWwindow* window;
	const char* title = "OpenGL Concepts";

	// initilizing library
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 0.0, 0.0f));

		//Its calculated in reverse order/or from right to left due to how its laid out in memory.
		//glm::mat4 mvp = proj * view * model;
		//shader.SetUniformMat4f("u_MVP", mvp);

		// Initialize the camera
		camera.MovementSpeed = 25.0f;

		Renderer renderer;

		Cube cube[] = {
			{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
			{glm::vec3(300.0f, 50.0f, -150.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}
		};
		LightSource lightSource(glm::vec3(110.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Process input */
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			processInput(window, camera, deltaTime);

			/* Render here */
			renderer.Clear();

			// Rendering
			// (Your code calls glfwSwapBuffers() etc.)
			float timeValue = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			float redValue = (sin(timeValue) / 1.0f * cos(timeValue / 2)) + 0.5f;
			float BlueValue = (cos(timeValue) / 1.65f) + 0.5f;



			//shader.Setuniform1i("u_Texture", 0);
			const float radius = 100.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
			glm::mat4 view = camera.GetViewMatrix();
			for (auto& c : cube)
			{

				//c.SetRotation(glm::vec3(timeValue * 50.0f, timeValue * 20.0f, 0.0f));

				//c.Update();
				c.Draw(renderer, proj, view, lightSource.GetPosition(), camera.Position);

			}
			lightSource.Draw(renderer, proj, view);
			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			glfwSwapInterval(1);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window, Camera& camera, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		std::cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << " " << camera.Pitch << std::endl;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}