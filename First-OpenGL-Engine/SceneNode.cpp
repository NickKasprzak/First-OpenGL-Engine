#include "SceneNode.h"

void SceneNode::SetPosition(glm::vec3 position)
{
	_position = position;
	UpdateModelMatrix();
}

void SceneNode::SetScale(glm::vec3 scale)
{
	_scale = scale;
	UpdateModelMatrix();
}

void SceneNode::SetRotation(glm::vec3 rotation)
{
	_rotation = rotation;
	UpdateModelMatrix();
}

void SceneNode::SetMesh(Mesh* mesh)
{
	_mesh = mesh;
}

void SceneNode::SetMaterial(Material* material)
{
	_material = material;
}

void SceneNode::UpdateModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, _position);
	model = glm::scale(model, _scale);
	//model = glm::rotate(glm::) just dont rotate for now, figure out a way to apply all rotations through quaternions or something
	_modelMatrix = model;
}