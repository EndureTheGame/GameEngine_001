#pragma once 
#include "VertexBufferLayout.h" 
#include "VertexBuffer.h" 
#include "Texture.h" 
#include "Camera.h" 
#include "glm/glm.hpp" 

class Renderer;

class LightSource
{

private:
	VertexArray va;
	VertexBuffer vb;
	ElementBuffer ebo;
	Shader shader;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 color;

public:
	LightSource(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	~LightSource();
	void Draw();
	void Update();

	//Setters 
	void SetPosition(const glm::vec3& pos);
	void SetRotation(const glm::vec3& rot);
	void SetScale(const glm::vec3& scale);
	void SetColor(const glm::vec3& color);

	//Getters
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
};