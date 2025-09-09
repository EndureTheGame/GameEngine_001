#include <glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "Scene.h"
#include "CameraNode.h"
#include "CubeNode.h"
#include "LightNode.h"
#include "Shader.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


void SetupDockSpace();
void processInput(GLFWwindow* window, Camera* camera, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


const unsigned int HEIGHT = 1080;
const unsigned int WIDTH = 1920;

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool stopCamera = false;
Camera* camera = nullptr;

static void glfw_error_callback(int error, const char* description);

int main()
{

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Concepts", nullptr, nullptr);
    if (!window) { std::cerr << "Failed to create GLFW window\n"; glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::cout << glGetString(GL_VERSION) << std::endl;
	
    Shader shader("res/shaders/Basic.shader");

    // ImGui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ImGui::GetStyle().Colors[ImGuiCol_DockingEmptyBg].w = 0.0f;


    glEnable(GL_DEPTH_TEST);

    // Scene setup
    camera = new Camera(glm::vec3(0.0f, 60.0f, 10.0f));
    Scene scene(camera);
    camera->MovementSpeed = 25.0f;

    auto cube1 = new Cube(glm::vec3(0.0f, 52.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    auto cube2 = new Cube(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    auto cubeNode1 = std::make_shared<CubeNode>(cube1);
    auto cubeNode2 = std::make_shared<CubeNode>(cube2);
    scene.GetRoot()->AddChild(cubeNode1);
    scene.GetRoot()->AddChild(cubeNode2);

    auto light = new LightSource(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    auto lightNode = std::make_shared<LightNode>(light);
    scene.GetRoot()->AddChild(lightNode);

    //Light Properties
    glm::vec3 lightPosition = glm::vec3(0.0f);
    glm::vec3 lightSpotPosition = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 lightDiffuse = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 lightSpecular = glm::vec3(1.0f, 1.0f, 1.0f);

    float materialShininess = 56.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera, deltaTime);
        Renderer::Clear();

		cube1->SetLightProperties(lightPosition, lightAmbient, lightDiffuse, lightSpecular, camera->GetPosition());
        cube1->SetSpotLightProperties(camera->Position, -camera->Front, glm::vec3(-0.2f, 1.0f, -0.3f), glm::vec3(1.0f, 0.0f, 0.0f), lightSpecular);
        cube1->SetMaterial(materialShininess);

        cube2->SetLightProperties(lightPosition, lightAmbient, lightDiffuse, lightSpecular, camera->GetPosition());
        cube2->SetSpotLightProperties(camera->Position, -camera->Front, glm::vec3(-0.2f, 1.0f, -0.3f), glm::vec3(1.0f, 0.0f, 0.0f), lightSpecular);
        cube2->SetMaterial(materialShininess);

		camera->SetProjection(camera->Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

        scene.Update(deltaTime);
        scene.Render();

        // ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        SetupDockSpace();

        ImGui::Begin("Light Control");
        ImGui::ColorEdit3("Light Color", (float*)&lightDiffuse);
        ImGui::End();

        ImGui::Begin("Light Position");
        ImGui::SliderFloat("X", &lightPosition.x, -100.0f, 100.0f);
        ImGui::SliderFloat("Y", &lightPosition.y, -100.0f, 100.0f);
        ImGui::SliderFloat("Z", &lightPosition.z, -100.0f, 100.0f);
        ImGui::End();

        ImGui::Begin("Scene Graph Debug");
        ImGui::Text("Root Children: %zu", scene.GetRoot()->GetChildren().size());
        for (size_t i = 0; i < scene.GetRoot()->GetChildren().size(); ++i) {
            ImGui::Text("Child %zu: %s", i, typeid(*scene.GetRoot()->GetChildren()[i]).name());
        }
        static bool wireframe = false;
        ImGui::Checkbox("Wireframe Mode", &wireframe);
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);


        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }

        glfwSwapBuffers(window);
        glfwSwapInterval(1);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window, Camera* camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        stopCamera = !stopCamera;
        glfwSetInputMode(window, GLFW_CURSOR, stopCamera ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }

    if (!stopCamera)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->ProcessKeyboard(RIGHT, deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!stopCamera)
    {
        if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        if (camera)
            camera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (camera)
        camera->ProcessMouseScroll(static_cast<float>(yoffset));

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
    // Calculate aspect ratio and use default values for fov, nearPlane, farPlane
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    camera->SetProjection(camera->Zoom, aspectRatio, 0.1f, 100.0f);
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


