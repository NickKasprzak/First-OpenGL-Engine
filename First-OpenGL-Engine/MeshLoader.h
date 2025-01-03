#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include <string>
#include <iostream>

#include "Mesh.h"

/*
* Update this to load a vector of meshes from
* an obj file. Have it combine all meshes in
* a model into one single mesh.
*/
class MeshLoader
{
public:
	MeshLoader() = default;
	~MeshLoader() = default;

	Mesh LoadMeshFromPath(std::string pathName);
private:
};