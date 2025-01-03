#include "TextureLoader.h"

Texture TextureLoader::LoadTextureFromPath(std::string texturePath)
{
	Texture texture;
	std::string path = texturePath;
	int width, height, numChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
	
	if (data)
	{
		GLenum format = GL_RGBA;
		switch (numChannels)
		{
		case 1:
			format = GL_DEPTH_COMPONENT;
			break;
		case 2:
			format = GL_DEPTH_STENCIL;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGBA;
			break;
		}
		
		texture.SetWrapMode(GL_REPEAT);
		texture.SetMinFilter(GL_LINEAR_MIPMAP_LINEAR);
		texture.SetMagFilter(GL_LINEAR);
		texture.Generate(width, height, format, format, GL_UNSIGNED_BYTE, true, data);
	}

	return texture;
}