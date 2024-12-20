#include "DirectionalLight.h"

glm::vec3 DirectionalLight::GetColor()
{ 
	return _color;
}

glm::vec3 DirectionalLight::GetDirection()
{ 
	return _direction;
}

void DirectionalLight::SetColor(glm::vec3 ambient)
{
	_color = glm::clamp(ambient, glm::vec3(0.0f), glm::vec3(1.0f));
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	_direction.x = fmod(direction.x, 360.0f);
	_direction.y = fmod(direction.y, 360.0f);
	_direction.z = fmod(direction.z, 360.0f);
}