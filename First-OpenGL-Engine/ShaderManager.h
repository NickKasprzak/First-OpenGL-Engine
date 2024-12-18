#pragma once
#include <vector>
#include <string>
#include <map>

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager() = default;
	~ShaderManager() = default;

	static ShaderManager* Instance();
	void Initialize();
	void Dispose();

	void RegisterShader(std::string shaderName, std::string vertPath, std::string fragPath);
	void RegisterShader(std::string shaderName, Shader shader);
	Shader* GetShader(std::string name);
private:
	static ShaderManager* _instance;
	std::map<std::string, Shader> _shaders;
};