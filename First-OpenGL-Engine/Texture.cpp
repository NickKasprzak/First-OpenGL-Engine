#include "Texture.h"

void Texture::Generate(int width, int height, GLenum internalFormat, GLenum format, GLenum type, bool hasMipmaps, void* data)
{
	_target = GL_TEXTURE_2D;
	_width = width;
	_height = height;
	_internalFormat = internalFormat;
	_format = format;
	_type = type;
	_hasMipmaps = hasMipmaps;

	glGenTextures(1, &_ID);

	Bind();
	glTexImage2D(_target, 0, _internalFormat, _width, _height, 0, _format, _type, data); // pass in 0 if no texture data?
	glTexParameteri(_target, GL_TEXTURE_WRAP_S, _wrapMode);
	glTexParameteri(_target, GL_TEXTURE_WRAP_T, _wrapMode);
	glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, _minFilter);
	glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, _magFilter);
	if (_hasMipmaps)
	{
		glGenerateMipmap(_target);
	}
	Unbind();
}

void Texture::Dispose()
{
	glDeleteTextures(1, &_ID);
	_ID = 0;
	_wrapMode = GL_REPEAT;
	_minFilter = GL_NEAREST;
	_magFilter = GL_NEAREST;
}

void Texture::Bind(int textureUnit)
{
	if (textureUnit >= 0)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
	}
	glBindTexture(_target, _ID);
}

void Texture::Unbind()
{
	glBindTexture(_target, 0);
}

void Texture::SetWrapMode(GLenum wrapMode)
{
	_wrapMode = wrapMode;

	if (_ID > 0)
	{
		Bind();
		glTexParameteri(_target, GL_TEXTURE_WRAP_S, _wrapMode);
		glTexParameteri(_target, GL_TEXTURE_WRAP_T, _wrapMode);
		Unbind();
	}
}

void Texture::SetMinFilter(GLenum minFilter)
{
	_minFilter = minFilter;

	if (_ID > 0)
	{
		Bind();
		glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, _minFilter);
		Unbind();
	}
}

void Texture::SetMagFilter(GLenum magFilter)
{
	_magFilter = magFilter;

	if (_ID > 0)
	{
		Bind();
		glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, _magFilter);
		Unbind();
	}
}