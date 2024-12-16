#include "Material.h"

void Material::Initialize(Shader* shader, unsigned int ID)
{
	_shader = shader;
	_ID = ID;
}

void Material::Dispose()
{
	_shader = nullptr;
	_ID = 0;
	_uniforms.clear();
	_textureUniforms.clear();
}

void Material::UseShader()
{
	_shader->Use();
}

unsigned int Material::GetID()
{ 
	return _ID; 
}

UniformData Material::GetUniform(std::string name)
{
	return _uniforms[name]; 
}

TextureData Material::GetTexture(std::string name)
{ 
	return _textureUniforms[name]; 
}

std::map<std::string, UniformData>* Material::GetAllUniforms()
{
	return &_uniforms;
}

std::map<std::string, TextureData>* Material::GetAllTextures()
{
	return &_textureUniforms;
}

Shader* Material::GetShader()
{
	return _shader;
}

void Material::SetBool(std::string name, bool value)
{
	if (_shader->HasUniform(name))
	{
		_uniforms[name].Type = UNIFORM_BOOL;
		_uniforms[name].Bool = value;
	}
}

void Material::SetInt(std::string name, int value)
{
	if (_shader->HasUniform(name))
	{
		_uniforms[name].Type = UNIFORM_INT;
		_uniforms[name].Int = value;
	}
}

void Material::SetFloat(std::string name, float value)
{
	if (_shader->HasUniform(name))
	{
		_uniforms[name].Type = UNIFORM_FLOAT;
		_uniforms[name].Float = value;
	}
}

void Material::SetVec3(std::string name, glm::vec3 value)
{
	if (_shader->HasUniform(name))
	{
		_uniforms[name].Type = UNIFORM_VEC3;
		_uniforms[name].Vec3 = value;
	}
}

void Material::SetMat3(std::string name, glm::mat4 value)
{
	if (_shader->HasUniform(name))
	{
		_uniforms[name].Type = UNIFORM_MAT3;
		_uniforms[name].Mat3 = value;
	}
}

void Material::SetMat4(std::string name, glm::mat4 value)
{
	if (_shader->HasUniform(name))
	{
		_uniforms[name].Type = UNIFORM_MAT4;
		_uniforms[name].Mat4 = value;
	}
}

void Material::SetTexture(std::string name, Texture* texture, unsigned int unit)
{
	if (_shader->HasUniform(name))
	{
		_textureUniforms[name].Unit = unit;
		_textureUniforms[name].Texture = texture;
	}

	/*
	* Make sure the sampler uniform has been bound
	* to the given texture ID for binding the texture's
	* data during drawing.
	*/
	_shader->Use();
	_shader->SetIntUniform(name, unit);
}