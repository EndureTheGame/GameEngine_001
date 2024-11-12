#include "LightSource.h" 

float tempPositions[] = {
	// Positions			 // Colors         // Texture Coords
	// Front face
	-20.0f, -20.0f,  20.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	 20.0f, -20.0f,  20.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 20.0f,  20.0f,  20.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-20.0f,  20.0f,  20.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	// Back face
	-20.0f, -20.0f, -20.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	 20.0f, -20.0f, -20.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 20.0f,  20.0f, -20.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-20.0f,  20.0f, -20.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	// Left face
	-20.0f, -20.0f, -20.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	-20.0f, -20.0f,  20.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	-20.0f,  20.0f,  20.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-20.0f,  20.0f, -20.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	// Right face
	 20.0f, -20.0f, -20.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	 20.0f, -20.0f,  20.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 20.0f,  20.0f,  20.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 20.0f,  20.0f, -20.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	 // Top face
	-20.0f,  20.0f,  20.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	 20.0f,  20.0f,  20.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 20.0f,  20.0f, -20.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-20.0f,  20.0f, -20.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
	// Bottom face
    -20.0f, -20.0f,  20.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	 20.0f, -20.0f,  20.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
	 20.0f, -20.0f, -20.0f,  0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
    -20.0f, -20.0f, -20.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f
};

unsigned int tempIndices[] = {
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

LightSource::LightSource(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) : position(pos), rotation(rot), scale(scale), vb(tempPositions, sizeof(tempPositions)), ebo(tempIndices, sizeof(tempIndices)), shader("Shaders/LightSource.shader")
{
	VertexBufferLayout layout; 
	layout.Push<float>(3); // Positions 
	layout.Push<float>(4); // Colors 
	layout.Push<float>(2); // Texture Coords 
	va.addBuffer(vb, layout); 
	shader.Bind();
}
LightSource::~LightSource()
{
	va.Undbind();
	vb.Unbind();
	ebo.Unbind();
	shader.Unbind();
}
void LightSource::Draw(Renderer& renderer, const glm::mat4& proj, const glm::mat4& view)
{ 
	glm::mat4 model = glm::mat4(1.0f); 
	model = glm::translate(model, position); 
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); 
	model = glm::scale(model, scale); 

	shader.Bind();
	shader.SetUniformMat4f("projection", proj); 
	shader.SetUniformMat4f("view", view); 
	shader.SetUniformMat4f("model", model); 
	//shader.Setuniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	renderer.Draw(va, ebo, shader);
}
void LightSource::Update()
{
}

void LightSource::SetPosition(const glm::vec3& pos)
{
	position = pos;
}

void LightSource::SetRotation(const glm::vec3& rot)
{
	rotation = rot;
}

void LightSource::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

glm::vec3 LightSource::GetRotation() const
{
	return rotation;
}

glm::vec3 LightSource::GetScale() const
{
	return	scale;
}

