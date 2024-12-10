#include "Texture.h"

void Texture::Generate(int width, int height, int numChannels, void* data)
{
	_width = width;
	_height = height;
	_target = GL_TEXTURE_2D;
	switch (numChannels)
	{
		case 1:
			_format = GL_DEPTH_COMPONENT;
			break;
		case 2:
			_format = GL_DEPTH_STENCIL;
			break;
		case 3:
			_format = GL_RGB;
			break;
		case 4:
			_format = GL_RGBA;
			break;
		default:
			break;
	}
	_internalFormat = _format;
	_sizeType = GL_UNSIGNED_BYTE;
	
	// set these with functions later
	_wrapMode = GL_REPEAT;
	_minFilter = GL_LINEAR_MIPMAP_LINEAR;
	_magFilter = GL_LINEAR;

	glGenTextures(1, &_ID);

	Bind();
	glTexImage2D(_target, 0, _internalFormat, _width, _height, 0, _format, _sizeType, data);
	glTexParameteri(_target, GL_TEXTURE_WRAP_S, _wrapMode);
	glTexParameteri(_target, GL_TEXTURE_WRAP_T, _wrapMode);
	glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, _minFilter);
	glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, _magFilter);
	glGenerateMipmap(_target);
	Unbind();
}

void Texture::Dispose()
{
	glDeleteTextures(1, &_ID);
}

void Texture::Bind(int textureUnit)
{
	if (textureUnit >= 0)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
	}
	glBindTexture(GL_TEXTURE_2D, _ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}