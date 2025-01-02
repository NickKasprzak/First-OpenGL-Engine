#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Uniform.h"

class Shader
{
public:
	Shader() = default;
	~Shader() = default;

	bool LoadProgram(std::string vertShaderSource, std::string fragShaderSource);
	void Use() const;

	bool HasUniform(std::string name);
	int GetUniformLocation(std::string name);

	void SetBoolUniform(const std::string& name, bool value);
	void SetIntUniform(const std::string& name, int value);
	void SetFloatUniform(const std::string& name, float value);
	void SetMat3Uniform(const std::string& name, glm::mat3 value);
	void SetMat4Uniform(const std::string& name, glm::mat4 value);
	void SetVec2Uniform(const std::string& name, glm::vec2 value);
	void SetVec3Uniform(const std::string& name, glm::vec3 value);
private:
	unsigned int _shaderProgramID = 0;

	/*
	* List of uniform names and data types pulled from the shader's
	* source for use in checking if a uniform exists and accessing
	* the uniform's location faster.
	* 
	* Shouldn't be exposed to the user.
	*/
	std::vector<Uniform> _uniforms = std::vector<Uniform>();
	//std::vector<VertexAttributes> _attributes;
};