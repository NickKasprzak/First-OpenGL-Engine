#include "Mesh.h"

void Mesh::BuildMesh(std::vector<Vertex> vertices)
{
	Dispose();

	_vertices = vertices;
	_indices = std::vector<unsigned int>();

	GenerateBuffers();
}

void Mesh::BuildMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	Dispose();

	_vertices = vertices;
	_indices = indices;

	GenerateBuffers();
}

void Mesh::BuildMesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals,
					 std::vector<glm::vec2> UVs, std::vector<unsigned int> indices)
{
	Dispose();

	for (int i = 0; i < positions.size(); i++)
	{
		Vertex newVert;
		newVert.position = positions[i];
		newVert.normal = normals[i];
		newVert.UV = UVs[i];
		_vertices.push_back(newVert);
	}

	this->_indices = indices;

	GenerateBuffers();
}

void Mesh::Dispose()
{
	if (VAO != 0) { glDeleteVertexArrays(1, &VAO); }
	if (VBO != 0) { glDeleteBuffers(1, &VBO); }
	if (EBO != 0) { glDeleteBuffers(1, &EBO); }

	_vertices.clear();
	_indices.clear();
}

void Mesh::Draw()
{
	glBindVertexArray(VAO);

	if (_indices.empty())
	{
		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
	}
	else if (!_indices.empty())
	{
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (!_indices.empty())
	{
		glGenBuffers(1, &EBO);
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(), &(_vertices[0]), GL_STATIC_DRAW);
	if (!_indices.empty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), &(_indices[0]), GL_STATIC_DRAW);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, UV)));

	glBindVertexArray(0);
}