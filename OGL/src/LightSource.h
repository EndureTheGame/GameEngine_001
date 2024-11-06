#pragma once 
#include "Renderer.h" 
#include "VertexBufferLayout.h" 
#include "VertexBuffer.h" 
#include "Texture.h" 
#include "Camera.h" 
#include "glm/glm.hpp" 

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
public:
	LightSource(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	~LightSource();
	void Draw(Renderer& renderer, const glm::mat4& proj, const glm::mat4& view);
	void Update();

	//Setters 
	void SetPosition(const glm::vec3& pos);
	void SetRotation(const glm::vec3& rot);
	void SetScale(const glm::vec3& scale);

	//Getters
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
};