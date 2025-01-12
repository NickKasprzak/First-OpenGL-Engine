#pragma once

#include "Mesh.h"
#include "MeshLoader.h"

/*
* Dont bother trying to do
* this procedurally yet, theres
* a lot of stuff that you don't
* know about generation. Finish
* the rendering command stuff,
* then move to procedular stuff.
* Like, thats a whole other project.
* 
* Just import a pre-made model
* for now.
* 
* Resources for later:
* https://github.com/caosdoar/spheres
* https://www.youtube.com/watch?v=ryVwLqhgl40
*/

class Cube : public Mesh
{
public:
	// wrong
	void BuildCube()
	{
		std::vector<glm::vec3> positions =
		{
			// Front - Tri 1
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f,  0.5f, -0.5f),

			// Front - Tri2
			glm::vec3(0.5f,  0.5f, -0.5f),
			glm::vec3(-0.5f,  0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			// Back - Tri1
			glm::vec3(-0.5f, -0.5f,  0.5f),
			glm::vec3(0.5f, -0.5f,  0.5f),
			glm::vec3(0.5f,  0.5f,  0.5f),

			// Back - Tri2
			glm::vec3(0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f, -0.5f,  0.5f),

			// Left - Tri1
			glm::vec3(-0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			// Left - Tri2
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f,  0.5f),

			// Right - Tri1
			glm::vec3(0.5f,  0.5f,  0.5f),
			glm::vec3(0.5f,  0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),

			// Right - Tri2
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f,  0.5f),
			glm::vec3(0.5f,  0.5f,  0.5f),

			// Bottom - Tri1
			glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f,  0.5f),

			// Bottom - Tri2
			glm::vec3(0.5f, -0.5f,  0.5f),
			glm::vec3(-0.5f, -0.5f,  0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f),

			// Top - Tri1
			glm::vec3(-0.5f,  0.5f, -0.5f),
			glm::vec3(0.5f,  0.5f, -0.5f),
			glm::vec3(0.5f,  0.5f,  0.5f),

			// Top - Tri2
			glm::vec3(0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f,  0.5f),
			glm::vec3(-0.5f,  0.5f, -0.5f)
		};

		std::vector<glm::vec3> normals =
		{
			// Front - Tri1
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),

			// Front - Tri2
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),
			glm::vec3(0.0f,  0.0f, -1.0f),

			// Back - Tri1
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),

			// Back - Tri2
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),
			glm::vec3(0.0f,  0.0f,  1.0f),

			// Left - Tri1
			glm::vec3(-1.0f,  0.0f,  0.0f),
			glm::vec3(-1.0f,  0.0f,  0.0f),
			glm::vec3(-1.0f,  0.0f,  0.0f),

			// Left - Tri2
			glm::vec3(-1.0f,  0.0f,  0.0f),
			glm::vec3(-1.0f,  0.0f,  0.0f),
			glm::vec3(-1.0f,  0.0f,  0.0f),

			// Right - Tri1
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),

			// Right - Tri2
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),

			// Bottom - Tri1
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),

			// Bottom - Tri2
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),
			glm::vec3(0.0f, -1.0f,  0.0f),

			// Top - Tri1
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),

			// Top - Tri2
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
		};

		std::vector<glm::vec2> UVs =
		{
			// Front - Tri1
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),

			// Front - Tri2
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),

			// Back - Tri1
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),

			// Back - Tri2
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			// Left - Tri1
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			// Left - Tri2
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),

			// Right - Tri1
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),

			// Right - Tri2
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),

			// Bottom - Tri1
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),

			// Bottom - Tri2
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),

			// Top - Tri1
			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),

			// Top - Tri2
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f)
		};

		BuildMesh(positions, normals, UVs, std::vector<unsigned int>());
	}
private:
};

class Sphere : public Mesh
{
public:
	void BuildSphere()
	{

	}
private:
};

class Quadsphere : public Mesh
{

};

class Plane : public Mesh
{
public:
	void BuildPlane()
	{
		std::vector<glm::vec3> positions =
		{
			glm::vec3(5.0f, -0.5f,  5.0f),
			glm::vec3(-5.0f, -0.5f,  5.0f),
			glm::vec3(-5.0f, -0.5f, -5.0f),

			glm::vec3(5.0f, -0.5f,  5.0f),
			glm::vec3(-5.0f, -0.5f, -5.0f),
			glm::vec3(5.0f, -0.5f, -5.0f)
		};

		std::vector<glm::vec3> normals =
		{
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),

			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f),
			glm::vec3(0.0f,  1.0f,  0.0f)
		};

		std::vector<glm::vec2> UVs =
		{
			glm::vec2(2.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 2.0f),

			glm::vec2(2.0f, 0.0f),
			glm::vec2(0.0f, 2.0f),
			glm::vec2(2.0f, 2.0f)
		};

		BuildMesh(positions, normals, UVs, std::vector<unsigned int>());
	}
};

class Quad : public Mesh
{
public:
	void BuildQuad()
	{
		std::vector<glm::vec3> positions =
		{
			glm::vec3(-1.0f,  1.0f,  0.0f),
			glm::vec3(-1.0f, -1.0f,  0.0),
			glm::vec3( 1.0f, -1.0f,  0.0),

			glm::vec3(-1.0f,  1.0f,  0.0),
			glm::vec3( 1.0f, -1.0f,  0.0),
			glm::vec3( 1.0f,  1.0f,  0.0)
		};

		std::vector<glm::vec3> normals =
		{
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),

			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f),
			glm::vec3(1.0f,  0.0f,  0.0f)
		};

		std::vector<glm::vec2> UVs =
		{
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f)
		};

		BuildMesh(positions, normals, UVs, std::vector<unsigned int>());
	}
};

// temp
class Primitives
{
public:
	static void BuildPrimitiveConstants()
	{
		MeshLoader meshLoader;
		cube = meshLoader.LoadMeshFromPath("C:/Users/AquaB/Downloads/Cube/cube.obj");
		sphere = meshLoader.LoadMeshFromPath("C:/Users/AquaB/Downloads/Sphere/sphere.obj");
		quad.BuildQuad();
	}

	static Mesh cube;
	static Mesh sphere;
	static Quad quad;
};