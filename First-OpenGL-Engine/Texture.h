#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
	void Generate(int width, int height, GLenum internalFormat, GLenum format, GLenum type, bool hasMipmaps, void* data);
	void Dispose();

	// Bind/Unbind texture to its respective target
	void Bind(int textureUnit = -1);
	void Unbind();

	unsigned int GetID() { return _ID; }

	void SetWrapMode(GLenum wrapMode);
	void SetMinFilter(GLenum minFilter);
	void SetMagFilter(GLenum magFilter);

private:
	unsigned int _ID = 0;

	int _width;
	int _height;
	GLenum _target;
	GLenum _internalFormat;
	GLenum _format;
	GLenum _type;
	bool _hasMipmaps = false; 

	GLenum _wrapMode = GL_REPEAT;
	GLenum _minFilter = GL_NEAREST;
	GLenum _magFilter = GL_NEAREST;
};