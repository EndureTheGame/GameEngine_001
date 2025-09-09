#include "Cube.h" 
#include <glm/gtx/string_cast.hpp>

float positions[] = {
	// Positions			 // Colors             // Texture Coords// Normals
	// Front face 
	-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  	0.0f, 0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f, 0.0f, 1.0f,
	 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f, 0.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f, 0.0f, 1.0f,
	//Back f1e
	-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  	0.0f, 0.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f, 0.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f, 0.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f, 0.0f, -1.0f,
	//Left f1e
	-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,	   -1.0f, 0.0f, 0.0f,
	-1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,	   -1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
	//Right ce
	 1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,      1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	1.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	1.0f, 0.0f, 0.0f,
	 //Top f1e
	-1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  	0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f, 1.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f, 1.0f, 0.0f,
	//Bottom1ace
	-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,		0.0f,-1.0f, 0.0f,
	 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f,-1.0f, 0.0f,
	 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f,-1.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f,-1.0f, 0.0f
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

Cube::Cube(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) : position(pos), rotation(rot), scale(scale), vb(positions, sizeof(positions)), ebo(indices, sizeof(indices)), shader("Shaders/BasicShader.shader"), texture("res/container2.png", "texture_diffuse"), texture2("res/container3.png", "texture_specular")
{
	shader.Bind();
	texture.Bind(0); 
	texture2.Bind(1);
	VertexBufferLayout layout; 
	layout.Push<float>(3); // Positions 
	layout.Push<float>(4); // Colors 
	layout.Push<float>(2); // Texture Coords 
	layout.Push<float>(3); // Normals
	va.addBuffer(vb, layout); 
}
Cube::~Cube()
{
	va.Undbind();
	vb.Unbind();
	ebo.Unbind();
	shader.Unbind();
	texture.Unbind();
	texture2.Unbind();
}
void Cube::Draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj)
{
	shader.Bind();
	texture.Bind(0);
	texture2.Bind(1);
	
	std::cout << "Drawing cube at position: " << glm::to_string(position) << std::endl;


	shader.SetUniformMat4f("model", model);
	shader.SetUniformMat4f("view", view);
	shader.SetUniformMat4f("projection", proj);

	shader.Setuniform3f("viewPosition", viewPosition.x, viewPosition.y, viewPosition.z);

	// Directional Light
	shader.Setuniform4f("directionalLight.direction", lightDirection.x, lightDirection.y, lightDirection.z, 0.0f);
	shader.Setuniform4f("directionalLight.ambient", lightAmbient.x, lightAmbient.y, lightAmbient.z, 1.0f);
	shader.Setuniform4f("directionalLight.diffuse", lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, 1.0f);
	shader.Setuniform4f("directionalLight.specular", lightSpecular.x, lightSpecular.y, lightSpecular.z, 1.0f);

	// Point Light
	shader.Setuniform4f("pointLight[0].position", lightPosition.x, lightPosition.y, lightPosition.z, 1.0f);
	shader.Setuniform4f("pointLight[0].ambient", lightAmbient.x, lightAmbient.y, lightAmbient.z, 1.0f);
	shader.Setuniform4f("pointLight[0].diffuse", lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, 1.0f);
	shader.Setuniform4f("pointLight[0].specular", lightSpecular.x, lightSpecular.y, lightSpecular.z, 1.0f);
	shader.Setuniform1f("pointLight[0].constant", 1.0f);
	shader.Setuniform1f("pointLight[0].linear", 0.0014f);
	shader.Setuniform1f("pointLight[0].quadratic", 0.00007f);

	// Spot Light
	shader.Setuniform4f("spotLight.position", lightSpotPosition.x, lightSpotPosition.y, lightSpotPosition.z, 1.0f);
	shader.Setuniform4f("spotLight.direction", lightSpotDirection.x, lightSpotDirection.y, lightSpotDirection.z, 0.0f);
	shader.Setuniform4f("spotLight.ambient", lightSpotAmbient.x, lightSpotAmbient.y, lightSpotAmbient.z, 1.0f);
	shader.Setuniform4f("spotLight.diffuse", lightSpotDiffuse.x, lightSpotDiffuse.y, lightSpotDiffuse.z, 1.0f);
	shader.Setuniform4f("spotLight.specular", lightSpotSpecular.x, lightSpotSpecular.y, lightSpotSpecular.z, 1.0f);
	shader.Setuniform1f("spotLight.constant", 1.0f);
	shader.Setuniform1f("spotLight.linear", 0.09f);
	shader.Setuniform1f("spotLight.quadratic", 0.032f);
	shader.Setuniform1f("spotLight.cutOff", glm::cos(glm::radians(10.0f)));
	shader.Setuniform1f("spotLight.outerCutOff", glm::cos(glm::radians(12.5f)));

	// Material
	shader.Setuniform1i("material.texture_diffuse", 0);
	shader.Setuniform1i("material.texture_specular", 1);
	shader.Setuniform1f("material.shininess", materialShininess);

	shader.Setuniform4f("objectColor", objectColor.x, objectColor.y, objectColor.z, objectColor.w);

	Renderer::Draw(va, ebo, shader, model);
	std::cout << "Directional Light Dir: " << glm::to_string(lightSpotDirection) << std::endl;
}

void Cube::Update()
{
	static float direction = 1.0f;
	position.x += direction * 0.01f;
	if (position.x > 0.5f) direction = -5;
	if (position.x < -0.5f) direction = 5;
}

void Cube::SetColor(glm::vec4 Color)
{

	objectColor = Color;
}

void Cube::SetPosition(const glm::vec3& pos)
{
	position = pos;
}

void Cube::SetRotation(const glm::vec3& rot)
{
	rotation = rot;
}

void Cube::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
}

void Cube::SetMaterial(float shininess)
{
	materialShininess = shininess;
}

void Cube::SetLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular, const glm::vec3& viewPos)
{
	this->lightPosition = lightPosition;
	this->lightAmbient = lightAmbient;
	this->lightDiffuse = lightDiffuse;
	this->lightSpecular = lightSpecular;
	this->viewPosition = viewPos;
}

void Cube::SetDirectionalLightProperties(const glm::vec3& lightDirection, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular)
{
	this->position = lightPosition;
	this->lightDirection = lightDirection;
	this->lightAmbient = lightAmbient;
	this->lightDiffuse = lightDiffuse;
	this->lightSpecular = lightSpecular;
}

void Cube::SetPointLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular)
{
	this->lightPosition = lightPosition;
	this->lightAmbient = lightAmbient;
	this->lightDiffuse = lightDiffuse;
	this->lightSpecular = lightSpecular;
	
}

void Cube::SetSpotLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightDirection, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular)
{
	this->lightSpotPosition = lightPosition;
	this->lightSpotDirection = lightDirection;
	this->lightSpotAmbient = lightAmbient;
	this->lightSpotDiffuse = lightDiffuse;
	this->lightSpotSpecular = lightSpecular;
}

const glm::mat4& Cube::GetTransform() const {
    static glm::mat4 transform;
    transform = glm::translate(glm::mat4(1.0f), position);
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    transform = glm::scale(transform, scale);
    return transform;
}

