#include "Shader.h"

bool Shader::LoadProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::string vertexSourceCode;
	std::string fragmentSourceCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	try
	{
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexShaderFile.rdbuf();
		fragmentStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexSourceCode = vertexStream.str();
		fragmentSourceCode = fragmentStream.str();
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to get shader source." << std::endl;
		return false;
	}
	const char* vertexSourcePointer = vertexSourceCode.c_str();
	const char* fragmentSourcePointer = fragmentSourceCode.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShader);

	int vertexSuccess;
	char infoLogVertex[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
	if (!vertexSuccess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
		std::cout << "Vertex shader compilation failed. Reason: " << infoLogVertex << std::endl;
		return false;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShader);

	int fragSuccess;
	char infoLogFrag[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);
	if (!fragSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFrag);
		std::cout << "Fragment shader compilation failed. Reason: " << infoLogFrag << std::endl;
		return false;
	}

	_shaderProgramID = glCreateProgram();
	glAttachShader(_shaderProgramID, vertexShader);
	glAttachShader(_shaderProgramID, fragmentShader);
	glLinkProgram(_shaderProgramID);

	int progSuccess;
	char infoLogProg[512];
	glGetProgramiv(_shaderProgramID, GL_LINK_STATUS, &progSuccess);
	if (!progSuccess)
	{
		glGetProgramInfoLog(_shaderProgramID, 512, NULL, infoLogProg);
		std::cout << "Shader program linking failed. Reason: " << infoLogProg << std::endl;
		return false;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

void Shader::Use() const
{
	glUseProgram(_shaderProgramID);
}

void Shader::SetBoolUniform(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(_shaderProgramID, name.c_str()), (int)value);
}

void Shader::SetIntUniform(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(_shaderProgramID, name.c_str()), value);
}

void Shader::SetFloatUniform(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(_shaderProgramID, name.c_str()), value);
}

void Shader::SetMat4Uniform(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(_shaderProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3Uniform(const std::string& name, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(_shaderProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3Uniform(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(_shaderProgramID, name.c_str()), 1, &value[0]);
}