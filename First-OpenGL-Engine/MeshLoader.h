#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include <string>
#include <iostream>

#include "Mesh.h"

class MeshLoader
{
public:
	MeshLoader() = default;
	~MeshLoader() = default;

	Mesh LoadMeshFromPath(std::string pathName);
private:
};