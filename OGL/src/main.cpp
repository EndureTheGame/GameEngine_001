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
#include "Camera3D.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>



#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


glm::vec3 cameraPos = glm::vec3(0.0f, 50.0f, 50.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
void processInput(GLFWwindow* window, Camera& camera)
{
	const float cameraSpeed = 25.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraTarget;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraTarget;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraTarget, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraTarget, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		std::cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;

	// Handle rotation (e.g., with mouse movement)
	double xpos = 400, ypos = 300;
	glfwGetCursorPos(window, &xpos, &ypos);
	static double lastX = xpos, lastY = ypos;
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.Rotate(xoffset, yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(void)
{
	GLFWwindow* window;

	const char* title = "OpenGL Concepts";
	int HEIGHT = 1080;
	int WIDTH = 1920;

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	{ 
	float positions[] = {
			// Positions			 // Colors         // Texture Coords
			// Front face
			-50.0f, -50.0f,  50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			 50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			 50.0f,  50.0f,  50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
			-50.0f,  50.0f,  50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
			// Back face
			-50.0f, -50.0f, -50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			 50.0f, -50.0f, -50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			 50.0f,  50.0f, -50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
			-50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
			// Left face
			-50.0f, -50.0f, -50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			-50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			-50.0f,  50.0f,  50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
			-50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
			// Right face
			 50.0f, -50.0f, -50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			 50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			 50.0f,  50.0f,  50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
			 50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
			 // Top face
			-50.0f,  50.0f,  50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			 50.0f,  50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			 50.0f,  50.0f, -50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
			-50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
			 // Bottom face
			-50.0f, -50.0f,  50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
			 50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
			 50.0f, -50.0f, -50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
			-50.0f, -50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f
	}; 

	unsigned int indices[] = {
		// Front face
		0, 1, 2,
		2, 3, 0,
		// Back face
		4, 5, 6,
		6, 7, 4,
		// Left face
		8, 9, 10,
		10, 11, 8,
		// Right face
		12, 13, 14,
		14, 15, 12,
		// Top face
		16, 17, 18,
		18, 19, 16,
		// Bottom face
		20, 21, 22,
		22, 23, 20
	};



		VertexArray va;
		VertexBuffer vb(positions, sizeof(positions));
		ElementBuffer ebo(indices, sizeof(indices));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		va.addBuffer(vb, layout);
		


		/*Layout
		//Possitions
		//GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0));
		//GlCall(glEnableVertexAttribArray(0));

		//Color
		//GlCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(2 * sizeof(float))));
		//GlCall(glEnableVertexAttribArray(1));

		//Texture
		//GlCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)))); 
		//GlCall(glEnableVertexAttribArray(2));
		*/

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			
		// Initialize the camera

		Camera camera(cameraPos, cameraTarget, up);
		
		glm::vec3 translation(0.0f, 0.0f, 0);
		glm::vec3 translationB(100.0f, 0.0f, 0);
		glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);


		//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 0.0, 0.0f));

		//Its calculated in reverse order/or from right to left due to how its laid out in memory.
		//glm::mat4 mvp = proj * view * model;

		Shader shader("BasicShader.shader");
		shader.Bind();
		Renderer renderer;

		Texture texture("res/container.jpg");
		texture.Bind();
		shader.Setuniform1i("u_Texture", 0);
		//shader.SetUniformMat4f("u_MVP", mvp);

		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		glm::vec3 cubePositions[] = {
			//           x         y         z
			glm::vec3(	 0.0f,     0.0f,     0.0f),
			glm::vec3( 300.0f,    50.0f,  -150.0f),
			glm::vec3(-300.0f,  -220.0f,  -250.0f),
			glm::vec3(-380.0f,  -200.0f,  -230.0f),
			glm::vec3( 240.0f,   -40.0f,  -350.0f),
			glm::vec3(-170.0f,   300.0f,  -750.0f),
			glm::vec3( 130.0f,  -200.0f,  -250.0f),
			glm::vec3( 150.0f,   200.0f,  -250.0f),
			glm::vec3( 150.0f,    20.0f,  -150.0f),
			glm::vec3(-130.0f,   100.0f,  -150.0f)
		};
		
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Process input */
			processInput(window, camera);

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			/* Render here */
			renderer.Clear();

			// Rendering
			




			// (Your code calls glfwSwapBuffers() etc.)
			float timeValue  = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			float redValue   = (sin(timeValue) / 1.0f * cos(timeValue / 2)) + 0.5f;
			float BlueValue  = (cos(timeValue) / 1.65f) + 0.5f;


			shader.Setuniform4f("u_Color", redValue, greenValue, BlueValue, 1.0f);
			//shader.Setuniform1i("u_Texture", 0);
				const float radius = 100.0f;
				float camX = sin(glfwGetTime()) * radius;
				float camZ = cos(glfwGetTime()) * radius;
				
				glm::mat4 view = camera.GetViewMatrix();
				camera.SetPosition(cameraPos);
				camera.SetTarget(cameraPos + cameraTarget);
				camera.SetUp(up);
			for (unsigned int i = 0; i < 10; i++)
			{

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
				//Its calculated in reverse order/or from right to left due to how its laid out in memory.
				glm::mat4 mvp = proj * view * model;

				shader.SetUniformMat4f("projection", proj);
				shader.SetUniformMat4f("view", view);
				shader.SetUniformMat4f("model", model);
				renderer.Draw(va, ebo, shader);
			}
			

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Properties");													// Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");									// Display some text (you can use a format strings too)
				//ImGui::Checkbox("Demo Window", &show_demo_window);						// Edit bools storing our window open/close state
				//ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat3("TranslationA", &cameraPos.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);         // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color);						// Edit 3 floats representing a color

				if (ImGui::Button("Button"))												// Buttons return true when clicked (most widgets return true when edited/activated)
				{
					counter++;
					translation.x++;
				}
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();  
			}

			//ImGui::ShowDemoWindow(); // Show demo window! :)c
			// (Your code clears your framebuffer, renders your other stuff etc.)
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			//glDrawArrays(GL_TRIANGLES, 0, 36);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			glfwSwapInterval(1);

			/* Poll for and process events */
			glfwPollEvents();

		}
		// Cleanup
		va.Undbind();
		vb.Unbind();
		ebo.Unbind();
		shader.Unbind();

	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}