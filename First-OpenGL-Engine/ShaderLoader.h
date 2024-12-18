#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Shader.h"

class ShaderLoader
{
public:
	Shader LoadShader(std::string shaderPath);
	Shader LoadShader(std::string vertPath, std::string fragPath);

	bool LoadSuccessful();
private:
	bool _loadSuccessful = false;
};