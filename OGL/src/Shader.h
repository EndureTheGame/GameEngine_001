#pragma once

#include <iostream>
#include <String>
#include <fstream>
#include <sstream>

#include <unordered_map>

#include <glm/ext/matrix_float4x4.hpp>


struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{

private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	public:

		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		ShaderProgramSource ParseShader(const std::string& filePath);

		void Setuniform1i(const std::string& name, int value);
		void Setuniform1f(const std::string& name, float value);
		void Setuniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		int GetUniformLocation(const std::string& name);
};