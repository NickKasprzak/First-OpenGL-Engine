#pragma once
#include <string>
#include <vector>
#include <map>

#include "Texture.h"
#include "Shader.h"
#include "Uniform.h"

class Material
{
public:
	void Initialize(Shader* shader, unsigned int ID);
	void Dispose();

	void UseShader();

	bool DepthTest = false;
	bool DepthWrite = false;
	GLenum DepthCompare = GL_LESS;

	// blending/translucency

	// shadows

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
	* Should NOT be used for anything that changes
	* on an object to object or frame to frame basis.
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

	// Loop through these when using the shader(?)
	std::map<std::string, UniformData> _uniforms;
	std::map<std::string, TextureData> _textureUniforms;
};