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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>




void SetupDockSpace();
void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void glfw_error_callback(int error, const char* description);

const unsigned int HEIGHT = 1080;
const unsigned int WIDTH = 1920;

// camera
Camera camera(glm::vec3(0.0f, 80.0f, -3.0f));

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool stopCamera = false;

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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	io.ConfigViewportsNoAutoMerge = true;
	io.ConfigViewportsNoTaskBarIcon = true;


	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();





	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.3f;
		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3f); // Setting alpha to 0.3 for slight transparency
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3f); // For child windows
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3f); // For pop-ups
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();




	glEnable(GL_DEPTH_TEST); 
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
			{glm::vec3(0.0f, 55.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
			{glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}
		};
		LightSource lightSource(glm::vec3(110.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		//Light Properties
		glm::vec3 lightPosition = glm::vec3(-0.2f, -1.0f, -0.3f);
		glm::vec3 lightSpotPosition = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

		//material properties
		glm::vec3 materialAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 materialDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 materialSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
		float materialShininess = 256.0f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			/* Poll for and process events */
			glfwPollEvents();

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
			float greenValue = 200.0f * sin(glfwGetTime());
			float redValue = -0.3f;	
			float BlueValue = 150.0f * cos(glfwGetTime());

			//shader.Setuniform1i("u_Texture", 0);
			const float radius = 100.0f;
			float camX = sin(glfwGetTime()) * radius;
			float camZ = cos(glfwGetTime()) * radius;
			glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
			glm::mat4 view = camera.GetViewMatrix();
			glm::vec3 viewPos = camera.Position;
			glm::vec3 front = camera.Front;
			for (auto& cube : cube) {
				//cube.SetLightProperties(lightPosition, lightAmbient, lightDiffuse, lightSpecular, viewPos);
				cube.SetSpotLightProperties(lightSpotPosition, front, lightAmbient, lightDiffuse, lightSpecular, viewPos);
				cube.SetMaterial(materialShininess);
				cube.Draw(renderer, proj, view);
			}
			lightSource.SetColor(lightDiffuse);
			lightSource.SetPosition(lightPosition);
			lightSource.Draw(renderer, proj, view);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			
			SetupDockSpace();

			// ImGui: Control light color 
			ImGui::Begin("Light Control"); 
			ImGui::ColorEdit3("Light Color", (float*)&lightDiffuse); 
			ImGui::End();

			ImGui::Begin("Light Position");
			ImGui::SliderFloat("X", &lightSpotPosition.x, -100.0f, 100.0f);
			ImGui::SliderFloat("Y", &lightSpotPosition.y, -100.0f, 100.0f);
			ImGui::SliderFloat("Z", &lightSpotPosition.z, -100.0f, 100.0f);
			ImGui::End();

			ImGui::ShowDemoWindow(); // Show demo window! :)

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Update and Render additional Platform Windows
			// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
			//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			glfwSwapInterval(1);

		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext(); 
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window, Camera& camera, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		if (!stopCamera) 
		{ 
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); stopCamera = true; 
		}
		else { 
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); stopCamera = false; 
		}
	}
	if (!stopCamera)
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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!stopCamera) {
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


void SetupDockSpace() {
	ImGuiIO& io = ImGui::GetIO();
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::Begin("DockSpace Demo", nullptr, window_flags);
	ImGui::PopStyleVar(2);

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

	ImGui::End();
}


