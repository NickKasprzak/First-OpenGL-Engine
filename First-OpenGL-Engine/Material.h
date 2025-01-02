#pragma once
#include <string>
#include <vector>
#include <map>

#include "Texture.h"
#include "Shader.h"
#include "Uniform.h"

/*
* Material class that acts as a container
* for any uniform data or OpenGL configurations
* a shader might need before the shader program
* is executed.
*/
class Material
{
public:
	void Initialize(Shader* shader, unsigned int ID);
	void Dispose();

	void UseShader();

	// Depth Config
	bool DepthTest = false;
	bool DepthWrite = false;
	GLenum DepthCompare = GL_LESS;

	// Blend Config

	// Shadow Config

	unsigned int GetID();
	UniformData GetUniform(std::string name);
	TextureData GetTexture(std::string name);
	std::map<std::string, UniformData>* GetAllUniforms();
	std::map<std::string, TextureData>* GetAllTextures();
	Shader* GetShader();

	/*
	* Used to set material specific values that
	* change how its correspond shader is configured.
	* 
	* Should NOT be used for anything that is object
	* specific (MVP matrices, colors, position data, etc.).
	* All of that gets set during the render command loop
	* through direct access to its shader.
	*/
	void SetBool(std::string name, bool value);
	void SetInt(std::string name, int value);
	void SetFloat(std::string name, float value);
	void SetVec3(std::string name, glm::vec3 value);
	void SetMat3(std::string name, glm::mat4 value);
	void SetMat4(std::string name, glm::mat4 value);
	void SetTexture(std::string name, Texture* texture, unsigned int unit);

private:
	Shader* _shader;
	unsigned int _ID;

	/*
	* Data corresponding to the uniforms the
	* shader attached to the material needs
	* to be rendered properly.
	*/
	std::map<std::string, UniformData> _uniforms;
	std::map<std::string, TextureData> _textureUniforms;
};