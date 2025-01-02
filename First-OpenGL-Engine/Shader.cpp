#include "Shader.h"

bool Shader::LoadProgram(std::string vertShaderSource, std::string fragShaderSource)
{
	// Compile and link shaders from given source
	const char* vertexSourcePointer = vertShaderSource.c_str();
	const char* fragmentSourcePointer = fragShaderSource.c_str();

	// Vertex compilation
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

	// Fragment compilation
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

	// Program linking
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

	// Load Uniforms
	int numUniforms;
	glGetProgramiv(_shaderProgramID, GL_ACTIVE_UNIFORMS, &numUniforms);
	_uniforms.resize(numUniforms);
	GLenum type;
	char nameBuff[512];

	for (int i = 0; i < numUniforms; i++)
	{
		glGetActiveUniform(_shaderProgramID, i, sizeof(char) * 512, NULL, NULL, &type, nameBuff);
		_uniforms[i].Name = std::string(nameBuff);
		_uniforms[i].Location = glGetUniformLocation(_shaderProgramID, nameBuff);
		switch (type)
		{
			case GL_BOOL:
				_uniforms[i].Type = UNIFORM_BOOL;
				break;
			case GL_INT:
				_uniforms[i].Type = UNIFORM_INT;
				break;
			case GL_FLOAT:
				_uniforms[i].Type = UNIFORM_FLOAT;
				break;
			case GL_FLOAT_VEC2:
				_uniforms[i].Type = UNIFORM_VEC2;
				break;
			case GL_FLOAT_VEC3:
				_uniforms[i].Type = UNIFORM_VEC3;
				break;
			case GL_FLOAT_MAT3:
				_uniforms[i].Type = UNIFORM_MAT3;
				break;
			case GL_FLOAT_MAT4:
				_uniforms[i].Type = UNIFORM_MAT4;
				break;
			case GL_SAMPLER_2D:
				// Int uniform since we bind sampler2Ds to a texture unit number
				_uniforms[i].Type = UNIFORM_INT;
				break;
			default:
				_uniforms[i].Type = UNIFORM_BOOL;
				break;
		}
	}

	return true;
}

void Shader::Use() const
{
	glUseProgram(_shaderProgramID);
}

bool Shader::HasUniform(std::string name)
{
	for (int i = 0; i < _uniforms.size(); i++)
	{
		if (_uniforms[i].Name == name)
		{
			return true;
		}
	}

	return false;
}

int Shader::GetUniformLocation(std::string name)
{
	for (int i = 0; i < _uniforms.size(); i++)
	{
		if (_uniforms[i].Name == name)
		{
			return _uniforms[i].Location;
		}
	}

	return -1;
}

void Shader::SetBoolUniform(const std::string& name, bool value)
{
	int location = GetUniformLocation(name);
	
	if (location >= 0)
	{
		glUniform1i(location, (int)value);
	}
}

void Shader::SetIntUniform(const std::string& name, int value)
{
	int location = GetUniformLocation(name);

	if (location >= 0)
	{
		glUniform1i(location, value);
	}
}

void Shader::SetFloatUniform(const std::string& name, float value)
{
	int location = GetUniformLocation(name);

	if (location >= 0)
	{
		glUniform1f(location, value);
	}
}

void Shader::SetMat3Uniform(const std::string& name, glm::mat3 value)
{
	int location = GetUniformLocation(name);

	if (location >= 0)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}

void Shader::SetMat4Uniform(const std::string& name, glm::mat4 value)
{
	int location = GetUniformLocation(name);

	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}

void Shader::SetVec2Uniform(const std::string& name, glm::vec2 value)
{
	int location = GetUniformLocation(name);

	if (location >= 0)
	{
		glUniform2fv(location, 1, &value[0]);
	}
}

void Shader::SetVec3Uniform(const std::string& name, glm::vec3 value)
{
	int location = GetUniformLocation(name);

	if (location >= 0)
	{
		glUniform3fv(location, 1, &value[0]);
	}
}