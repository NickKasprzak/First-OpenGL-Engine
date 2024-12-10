#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include <stb/stb_image.h>

#include <string>

#include "Mesh.h"

class MeshLoader
{
public:
	MeshLoader() = default;
	~MeshLoader() = default;

	Mesh LoadMeshFromPath(std::string pathName);
private:
	Texture LoadTexture();
};