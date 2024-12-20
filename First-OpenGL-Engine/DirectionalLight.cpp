#include "DirectionalLight.h"

glm::vec3 DirectionalLight::GetAmbient()
{ 
	return _ambientColor;
}

glm::vec3 DirectionalLight::GetDiffuse()
{ 
	return _diffuseColor; 
}

glm::vec3 DirectionalLight::GetSpecular()
{ 
	return _specularColor; 
}

glm::vec3 DirectionalLight::GetDirection()
{ 
	return _direction;
}

void DirectionalLight::SetAmbient(glm::vec3 ambient)
{
	_ambientColor = glm::clamp(ambient, glm::vec3(0.0f), glm::vec3(1.0f));
}

void DirectionalLight::SetDiffuse(glm::vec3 diffuse)
{
	_diffuseColor = glm::clamp(diffuse, glm::vec3(0.0f), glm::vec3(1.0f));
}

void DirectionalLight::SetSpecular(glm::vec3 specular)
{
	_specularColor = glm::clamp(specular, glm::vec3(0.0f), glm::vec3(1.0f));
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	_direction.x = fmod(direction.x, 360.0f);
	_direction.y = fmod(direction.y, 360.0f);
	_direction.z = fmod(direction.z, 360.0f);
}