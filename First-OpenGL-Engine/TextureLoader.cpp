#include "TextureLoader.h"

Texture TextureLoader::LoadTextureFromPath(std::string texturePath)
{
	Texture texture;
	std::string path = texturePath;
	int width, height, numChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
	
	if (data)
	{
		texture.Generate(width, height, numChannels, data);
	}

	return texture;
}