#pragma once 
#include "Renderer.h" 
#include "VertexBufferLayout.h" 
#include "VertexBuffer.h" 
#include "Texture.h" 
#include "Camera.h" 
#include "glm/glm.hpp" 

class Cube 
{ 

	private:
		VertexArray va; 
		VertexBuffer vb; 
		ElementBuffer ebo; 
		Shader shader; 
		Texture texture; 
		glm::vec3 position; 
		glm::vec3 rotation; 
		glm::vec3 scale; 
	public: 
		Cube(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale); 
		~Cube();
		void Draw(Renderer& renderer, const glm::mat4& proj, const glm::mat4& view); 
		void Update(); 

		//Setters 
		void SetPosition(const glm::vec3& pos); 
		void SetRotation(const glm::vec3& rot); 
		void SetScale(const glm::vec3& scale);
};