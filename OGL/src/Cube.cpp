#include "Cube.h" 

float positions[] = {
	// Positions			 // Colors                // Texture Coords		// Normals
	// Front face 
	-50.0f, -50.0f,  50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  	0.0f, 0.0f, 1.0f,
	 50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f, 0.0f, 1.0f,
	 50.0f,  50.0f,  50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f, 0.0f, 1.0f,
	-50.0f,  50.0f,  50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f, 0.0f, 1.0f,
	// Back face
	-50.0f, -50.0f, -50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  	0.0f, 0.0f, -1.0f,
	 50.0f, -50.0f, -50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f, 0.0f, -1.0f,
	 50.0f,  50.0f, -50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f, 0.0f, -1.0f,
	-50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f, 0.0f, -1.0f,
	// Left face
	-50.0f, -50.0f, -50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-50.0f,  50.0f,  50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	// Right face
	 50.0f, -50.0f, -50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
	 50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	1.0f, 0.0f, 0.0f,
	 50.0f,  50.0f,  50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	1.0f, 0.0f, 0.0f,
	 50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	1.0f, 0.0f, 0.0f,
	 // Top face
	-50.0f,  50.0f,  50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  	0.0f, 1.0f, 0.0f,
	 50.0f,  50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f, 1.0f, 0.0f,
	 50.0f,  50.0f, -50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f, 1.0f, 0.0f,
	-50.0f,  50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f, 1.0f, 0.0f,
	// Bottom face
    -50.0f, -50.0f,  50.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,	0.0f,-1.0f, 0.0f,
	 50.0f, -50.0f,  50.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,  	0.0f,-1.0f, 0.0f,
	 50.0f, -50.0f, -50.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,  	0.0f,-1.0f, 0.0f,
    -50.0f, -50.0f, -50.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,  	0.0f,-1.0f, 0.0f
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

	//light properties
	shader.Setuniform3f("light.position", lightPosition.x, lightPosition.y, lightPosition.z);
	shader.Setuniform3f("light.ambient", lightAmbient.x, lightAmbient.y, lightAmbient.z);
	shader.Setuniform3f("light.diffuse", lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
	shader.Setuniform3f("light.specular", lightSpecular.x, lightSpecular.y, lightSpecular.z);
	shader.Setuniform3f("viewPosition", viewPosition.x, viewPosition.y, lightAmbient.z);

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

void Cube::SetLightProperties(const glm::vec3& lightPos, const glm::vec3& lightAmbient, const glm::vec3& lightDiffuse, const glm::vec3& lightSpecular, const glm::vec3& viewPos)
{
	this->lightPosition = lightPos;
	this->lightAmbient = lightAmbient;
	this->lightDiffuse = lightDiffuse;
	this->lightSpecular = lightSpecular;
	this->viewPosition = viewPos;
}
