#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
	// Generate as empty
	void Generate();
	// Generate with existing data
	void Generate(int width, int height, int nrComponents, void* data);

	void Dispose();

	// Bind/Unbind texture to its respective target
	void Bind(int textureUnit = -1);
	void Unbind();

	// Set texture's corresponding uniform name for binding to a shader
	void SetType(std::string uniformName) { uniformName = uniformName; }

	unsigned int GetID() { return _ID; }
	std::string GetType() { return uniformName; }
	std::string GetPath() { return _path; }

private:
	unsigned int _ID;
	std::string uniformName;
	std::string _path;

	int _width;
	int _height;
	GLenum _target;
	GLenum _internalFormat;
	GLenum _format;
	GLenum _sizeType;

	GLenum _wrapMode;
	GLenum _minFilter;
	GLenum _magFilter;
};