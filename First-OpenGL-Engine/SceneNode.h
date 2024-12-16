#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Material.h"

class SceneNode
{
public:
	friend class Renderer;

	void SetPosition(glm::vec3 position);
	void SetScale(glm::vec3 scale);
	void SetRotation(glm::vec3 rotation);
	void SetMesh(Mesh* mesh);
	void SetMaterial(Material* material);

private:
	void UpdateModelMatrix();

	Mesh* _mesh = nullptr;

	/*
	* Consider not putting this here. Instead,
	* have an ID corresponding to the render
	* techniques that the node will use.
	* 
	* It will make batching them much easier since
	* we'll be able to render by technique/material
	* and avoid having to redundantly set the
	* same data over and over for the same stuff.
	* 
	* There could be a material/technique manager
	* that the renderer would have access to and
	* could index just as fast.
	*/
	Material* _material = nullptr;

	glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
};