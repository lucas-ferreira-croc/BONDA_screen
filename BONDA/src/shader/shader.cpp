#include "shader.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ShaderCode shaderCode = loadCode(vertexPath, fragmentPath);

	const char* vShaderCode = shaderCode.vertexCode.c_str();
	const char* fShaderCode = shaderCode.fragmentCode.c_str();

	unsigned int vertex, fragment;

	//vertex = compile(vShaderCode, ShaderType::VERTEX);
	
	vertex = compile(vShaderCode, ShaderType::VERTEX);

	fragment = compile(fShaderCode, ShaderType::FRAGMENT);

	id = createProgram(vertex, fragment);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, float v0, float v1) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), v0, v1);
}

void Shader::setVec4(const std::string& name, float v0, float v1, float v2, float v3) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), v0, v1, v2, v3);
}

ShaderCode Shader::loadCode(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (std::ifstream::failure& e) {
		std::cout << "Error loadgind file" << e.what() << std::endl;
	}
	return ShaderCode{ vertexCode, fragmentCode };
}

unsigned int Shader::compile(const char* shaderCode, ShaderType type)
{
	unsigned int shader = glCreateShader(type == ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);  //glCreateShader(type == ShaderType::VERTEX ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);;
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, type);
	return shader;
}

unsigned int Shader::createProgram(unsigned int vertex, unsigned int fragment)
{
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertex);
	glAttachShader(programID, fragment);
	glLinkProgram(programID);

	checkCompileErrors(programID, ShaderType::PROGRAM);
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return programID;
}

void Shader::checkCompileErrors(unsigned int shader, ShaderType type)
{
	int success;
	char infoLog[1024];
	if (type != ShaderType::PROGRAM)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: program "<< (type == ShaderType::VERTEX ? " vertex" : "fragment") <<  "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " <<  "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
