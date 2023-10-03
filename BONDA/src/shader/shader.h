#pragma once

#include <string>

enum class ShaderType
{
	VERTEX = 0,
	FRAGMENT,
	PROGRAM
};

struct ShaderCode
{
	std::string vertexCode;
	std::string fragmentCode;
};

class Shader
{
public:
	
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setVec2(const std::string& name, float v0, float v1) const;
	
	void setVec4(const std::string& name, float v0, float v1, float v2, float v3) const;

	unsigned int id;
private:
	void checkCompileErrors(unsigned int shader, ShaderType type);

	ShaderCode loadCode(const char* vertexPath, const char* fragmentPath);

	unsigned int compile(const char* shaderCode, ShaderType type);

	unsigned int createProgram(unsigned int vertex, unsigned int fragment);
};

