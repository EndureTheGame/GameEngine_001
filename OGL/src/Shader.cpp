#include "Shader.h"
#include "Renderer.h"



Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
	std::cout << "Loading shader from path: " << filepath << std::endl;
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexShader, source.FragmentShader);
	std::cout << "Shader compiled and linked successfully. ID: " << m_RendererID << std::endl;
}


Shader::~Shader()
{
	GlCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GlCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GlCall(glUseProgram(0));
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#Shader") != std::string::npos)
		{
			if (line.find("Vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("Fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

void Shader::Setuniform1i(const std::string& name, int value)
{
	GlCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::Setuniform1f(const std::string& name, float value)
{
	GlCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::Setuniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GlCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	if (location == -1) {
		std::cout << "Warning: Uniform '" << name << "' not found or not used." << std::endl;
		return;  // Avoid calling glUniformMatrix4fv with an invalid location
	}
	std::cout << "Setting uniform '" << name << "' at location " << location << std::endl;
	GlCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handle
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to Compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}


	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(program, vs));
	GlCall(glAttachShader(program, fs));
	GlCall(glLinkProgram(program));
	GlCall(glValidateProgram(program));

	GlCall(glDeleteShader(vs));
	GlCall(glDeleteShader(fs));

	return program;
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GlCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1) {
		std::cout << "Warning: Uniform '" << name << "' does not exist!" << std::endl;
	}
	else {
		std::cout << "Uniform '" << name << "' retrieved with location: " << location << std::endl;
	}

	m_UniformLocationCache[name] = location;
	return location;
}

