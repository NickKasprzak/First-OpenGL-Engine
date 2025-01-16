#include "ShaderManager.h"
#include "ShaderLoader.h"

ShaderManager* ShaderManager::_instance = nullptr;

void ShaderManager::Initialize()
{
	// Load all default shaders (geometry, lighting, shadow, etc.)
	RegisterShader("GeometryPass", "geometryPass.vert", "geometryPass.frag");
	RegisterShader("DirectionalLightPass", "lightPass.vert", "dirLightPass.frag");
	RegisterShader("PointLightPass", "lightPass.vert", "pointLightPass.frag");
	// spotlight pass
	RegisterShader("DirLightShadowMapPass", "dirLightShadowMapPass.vert", "dirLightShadowMapPass.frag");
	// point shadow pass
}

void ShaderManager::Dispose()
{
	_shaders.clear();
}

ShaderManager* ShaderManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new ShaderManager();
	}
	return _instance;
}

void ShaderManager::RegisterShader(std::string shaderName, std::string vertPath, std::string fragPath)
{
	ShaderLoader loader;
	Shader shader = loader.LoadShader(vertPath, fragPath);

	if (loader.LoadSuccessful())
	{
		_shaders[shaderName] = shader;
		return;
	}

	else if (!loader.LoadSuccessful())
	{
		std::cout << "Failed to loader shader " + shaderName + "." << std::endl;
		return;
	}
}

void ShaderManager::RegisterShader(std::string shaderName, Shader shader)
{
	_shaders[shaderName] = shader;
}

Shader* ShaderManager::GetShader(std::string shaderName)
{
	if (_shaders.find(shaderName) != _shaders.end())
	{
		return &_shaders[shaderName];
	}

	return NULL;
}