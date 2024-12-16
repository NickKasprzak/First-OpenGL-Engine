#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Uniform.h"

class Shader
{
public:
	Shader() = default;

	bool LoadProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
	void Use() const;

	bool HasUniform(std::string name);

	void SetBoolUniform(const std::string& name, bool value) const;
	void SetIntUniform(const std::string& name, int value) const;
	void SetFloatUniform(const std::string& name, float value) const;
	void SetMat4Uniform(const std::string& name, glm::mat4 value) const;
	void SetMat3Uniform(const std::string& name, glm::mat3 value) const;
	void SetVec3Uniform(const std::string& name, glm::vec3 value) const;
private:
	unsigned int _shaderProgramID;
	std::vector<Uniform> _uniforms;
	//std::vector<VertexAttributes> _attributes;
};