#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
	void Generate(int width, int height, int nrComponents, void* data);
	void Dispose();

	void Bind(int textureUnit = -1);
	void Unbind();

	void SetType(std::string type) { _type = type; }

	unsigned int GetID() { return _ID; }
	std::string GetType() { return _type; }
	std::string GetPath() { return _path; }

private:
	unsigned int _ID;
	std::string _type;
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