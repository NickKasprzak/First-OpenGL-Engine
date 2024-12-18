#pragma once

#include "Mesh.h"

class Cube : public Mesh
{
public:
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