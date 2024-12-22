#pragma once
#include <glm/glm.hpp>

/*
* Have a dirty flag so the renderer
* knows not to update the directional
* light shader's uniforms if it doesn't
* change at all?
*/
class DirectionalLight
{
public:
	DirectionalLight() = default;
	~DirectionalLight() = default;

	glm::vec3 GetColor();
	glm::vec3 GetDirection();

	void SetColor(glm::vec3 color);
	void SetDirection(glm::vec3 direction);

private:
	glm::vec3 _color = glm::vec3(0.5f);
	glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
};