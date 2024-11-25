#include "Cube.h" 

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

Cube::Cube(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) : position(pos), rotation(rot), scale(scale), vb(positions, sizeof(positions)), ebo(indices, sizeof(indices)), shader("Shaders/BasicShader.shader"), texture("res/container2.png"), texture2("res/container3.png")
{
	VertexBufferLayout layout; 
	layout.Push<float>(3); // Positions 
	layout.Push<float>(4); // Colors 
	layout.Push<float>(2); // Texture Coords 
	layout.Push<float>(3); // Normals
	va.addBuffer(vb, layout); 
	texture.Bind(0); 
	texture2.Bind(1);
	shader.Bind();
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
void Cube::Draw(Renderer& renderer, const glm::mat4& proj, const glm::mat4& view)
{ 
	glm::mat4 model = glm::mat4(1.0f); 
	model = glm::translate(model, position); 
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); 
	model = glm::scale(model, scale); 
	shader.Bind();
	texture.Bind(0);
	texture2.Bind(1);
	shader.SetUniformMat4f("projection", proj); 
	shader.SetUniformMat4f("view", view); 
	shader.SetUniformMat4f("model", model); 
	shader.Setuniform3f("viewPosition", viewPosition.x, viewPosition.y, lightAmbient.z);


	//Directional light properties
	shader.Setuniform4f("directionalLight.direction", -0.2f, -1.0f, -0.3f, 0.0f);
	shader.Setuniform4f("directionalLight.ambient", 0.05f, 0.05f, 0.05f, 1.0f);
	shader.Setuniform4f("directionalLight.diffuse", 0.4f, 0.4f, 0.4f, 1.0f);
	shader.Setuniform4f("directionalLight.specular", 0.5f, 0.5f, 0.5f, 1.0f);

	//light properties
	shader.Setuniform4f("pointLight[0].position", 0.0f, 10.0f, 0.0f, 1.0f);
	shader.Setuniform4f("pointLight[0].ambient",  lightAmbient.x, lightAmbient.y, lightAmbient.z, 1.0f);
	shader.Setuniform4f("pointLight[0].diffuse",  lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, 1.0f);
	shader.Setuniform4f("pointLight[0].specular", lightSpecular.x, lightSpecular.y, lightSpecular.z, 1.0f);
	shader.Setuniform1f("pointLight[0].constant", 1.0f);
	shader.Setuniform1f("pointLight[0].linear", 0.0014f);
	shader.Setuniform1f("pointLight[0].quadratic", 0.00007f);
	//spot light properties
	shader.Setuniform4f("spotLight.position", lightSpotPosition.x, lightSpotPosition.y, lightSpotPosition.z, 1.0f);
	shader.Setuniform4f("spotLight.direction", 0.0f, -1.0f, 0.0f, 0.0f);
	shader.Setuniform4f("spotLight.ambient", 0.05f, 0.05f, 0.05f, 1.0f);
	shader.Setuniform4f("spotLight.diffuse", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.Setuniform4f("spotLight.specular", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.Setuniform1f("spotLight.constant", 1.0f);
	shader.Setuniform1f("spotLight.linear", 0.9f);
	shader.Setuniform1f("spotLight.quadratic", 0.82f);
	shader.Setuniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.Setuniform1f("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

	//material properties
	//shader.Setuniform3f("material.ambient", materialAmbient.x, materialAmbient.y, materialAmbient.z);
	shader.Setuniform1i("material.texture_diffuse", 0);
	shader.Setuniform1i("material.texture_specular",1);
	shader.Setuniform1f("material.shininess", materialShininess);

	renderer.Draw(va, ebo, shader);
}
void Cube::Update()
{
	static float direction = 1.0f;
	position.x += direction * 0.01f;
	if (position.x > 0.5f) direction = -5;
	if (position.x < -0.5f) direction = 5;
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

void Cube::SetSpotLightProperties(const glm::vec3& lightPosition, const glm::vec3& lightDirection, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular, const glm::vec3& viewPos)
{
	this->lightPosition = lightPosition;
	this->lightDirection = lightDirection;
	this->lightAmbient = lightAmbient;
	this->lightDiffuse = lightDiffuse;
	this->lightSpecular = lightSpecular;
	this->viewPosition = viewPos;
}
