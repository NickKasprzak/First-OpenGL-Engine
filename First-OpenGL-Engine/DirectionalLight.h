#pragma once
#include <glm/glm.hpp>

/*
* Have a dirty flag so the renderer
* knows not to update the directional
* light shader's uniforms if it doesn't
* change at all?
*/

// do we really need all these getters and setters?
class DirectionalLight
{
public:
	DirectionalLight() = default;
	~DirectionalLight() = default;

	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	glm::vec3 GetDirection();

	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);
	void SetDirection(glm::vec3 direction);

private:
	glm::vec3 _ambientColor = glm::vec3(0.5f);
	glm::vec3 _diffuseColor = glm::vec3(0.5f);
	glm::vec3 _specularColor = glm::vec3(0.5f);
	glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
};