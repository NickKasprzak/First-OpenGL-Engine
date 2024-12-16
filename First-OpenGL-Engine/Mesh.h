#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 UV;
};

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

	void BuildMesh(std::vector<Vertex> vertices);
	void BuildMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void BuildMesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
				   std::vector<glm::vec2> texCoords, std::vector<unsigned int> indices);
	void Dispose();

	void Draw();

private:
	void GenerateBuffers();

	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
};