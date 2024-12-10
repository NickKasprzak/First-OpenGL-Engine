#pragma once
#include <stb/stb_image.h>
#include <string>

#include "Texture.h"

class TextureLoader
{
public:
	Texture LoadTextureFromPath(std::string texturePath);
private:
};