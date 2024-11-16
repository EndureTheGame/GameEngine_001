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
		Texture texture2;

		glm::vec3 position; 
		glm::vec3 rotation; 
		glm::vec3 scale; 

		//glm::vec3 materialAmbient; 
		//glm::vec3 materialDiffuse; 
		//glm::vec3 materialSpecular; 
		float materialShininess; 
		
		glm::vec3 lightPosition; 
		glm::vec3 lightAmbient; 
		glm::vec3 lightDiffuse; 
		glm::vec3 lightSpecular; 
		glm::vec3 viewPosition;

	public: 
		Cube(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale); 
		~Cube();
		void Draw(Renderer& renderer, const glm::mat4& proj, const glm::mat4& view);
		void Update(); 

		//Setters 
		void SetPosition(const glm::vec3& pos); 
		void SetRotation(const glm::vec3& rot); 
		void SetScale(const glm::vec3& scale);
		void SetMaterial(float shininess);
		void SetLightProperties(const glm::vec3& lightPos, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular, const glm::vec3& viewPos);

		//Getters 
		glm::vec3 GetPosition() const; 
		glm::vec3 GetRotation() const; 
		glm::vec3 GetScale() const;
};