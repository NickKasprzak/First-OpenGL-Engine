#include "MeshLoader.h"

// Only grabs the first mesh for now.
// Doesn't load textures yet either.
Mesh MeshLoader::LoadMeshFromPath(std::string pathName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(pathName, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Failed to load mesh. Reason: " << importer.GetErrorString() << std::endl;
		return Mesh();
	}

	aiMesh* mesh = scene->mMeshes[0];

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vert;
		glm::vec3 data;

		data.x = mesh->mVertices[i].x;
		data.y = mesh->mVertices[i].y;
		data.z = mesh->mVertices[i].z;
		vert.position = data;

		if (mesh->HasNormals())
		{
			data.x = mesh->mNormals[i].x;
			data.y = mesh->mNormals[i].y;
			data.z = mesh->mNormals[i].z;
			vert.normal = data;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 uvData;
			uvData.x = mesh->mTextureCoords[0][i].x;
			uvData.y = mesh->mTextureCoords[0][i].y;
			vert.UV = uvData;
		}
		else
		{
			vert.UV = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vert);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh newMesh;
	newMesh.BuildMesh(vertices, indices);
	return newMesh;
}