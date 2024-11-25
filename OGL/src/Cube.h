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

		//Directional light properties 
		glm::vec3 lightDirection; 
		glm::vec3 lightDirAmbient; 
		glm::vec3 lightDirDiffuse; 
		glm::vec3 lightDirSpecular;

		//Point light properties 
		glm::vec3 lightPointPosition; 
		glm::vec3 lightPointAmbient; 
		glm::vec3 lightPointDiffuse; 
		glm::vec3 lightPointSpecular;

		//Spot light properties 
		glm::vec3 lightSpotPosition; 
		glm::vec3 lightSpotDirection; 
		glm::vec3 lightSpotAmbient; 
		glm::vec3 lightSpotDiffuse; 
		glm::vec3 lightSpotSpecular;

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
		void SetLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular, const glm::vec3& viewPos);
		void SetDirectionalLightProperties(const glm::vec3& lightDirection, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular);
		void SetPointLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular);
		void SetSpotLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightDirection, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular, const glm::vec3& viewPos);



		//Getters 
		glm::vec3 GetPosition() const; 
		glm::vec3 GetRotation() const; 
		glm::vec3 GetScale() const;
};