#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Input.h"
#include "Camera.h"

class Application {
public:
    Application(int width, int height, const std::string& title);
    void Run();

private:
	Input input;
    Window window;
    Renderer renderer;
    VertexArray vao;
    ElementBuffer ebo;
    Shader shader;
    Camera camera;

    void Initialize();
    void Render();
};

#endif // APPLICATION_H
