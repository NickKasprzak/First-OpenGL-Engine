#include "ShaderLoader.h"

Shader ShaderLoader::LoadShader(std::string shaderPath)
{
	// get vertex and fragment shader source from given folder path
	_loadSuccessful = false;
	return Shader();
}

Shader ShaderLoader::LoadShader(std::string vertPath, std::string fragPath)
{
	std::string vertexSourceCode;
	std::string fragmentSourceCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	try
	{
		vertexShaderFile.open(vertPath);
		fragmentShaderFile.open(fragPath);

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
		_loadSuccessful = false;
		return Shader();
	}

	Shader newShader;
	_loadSuccessful = newShader.LoadProgram(vertexSourceCode, fragmentSourceCode);
	return newShader;
}

bool ShaderLoader::LoadSuccessful()
{
	return _loadSuccessful;
}