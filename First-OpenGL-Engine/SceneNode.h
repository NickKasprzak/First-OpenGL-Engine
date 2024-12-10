#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"

class SceneNode
{
public:
	void Draw(Shader* shader);

	void SetPosition(glm::vec3 position);
	void SetScale(glm::vec3 scale);
	void SetRotation(glm::vec3 rotation);
	void SetMesh(Mesh* mesh);

private:
	void UpdateModelMatrix();

	Mesh* _mesh = nullptr;

	// move this stuff to a scene node object later
	// renderable should be an abstract class of sorts that can draw anything
	// like a GUI element, 3d model, billboarded object, etc.
	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
};