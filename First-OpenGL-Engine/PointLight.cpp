#include "PointLight.h"

glm::vec3 PointLight::GetPosition()
{
	return _position;
}

glm::vec3 PointLight::GetColor()
{
	return _color;
}

float PointLight::GetRadius()
{
	return _radius;
}

float PointLight::GetIntensity()
{
	return _intensity;
}

void PointLight::SetPosition(glm::vec3 position)
{
	_position = position;
}

void PointLight::SetColor(glm::vec3 color)
{
	_color = glm::clamp(color, glm::vec3(0.0f), glm::vec3(1.0f));
}

void PointLight::SetRadius(float radius)
{
	_radius = fmax(radius, 0.0f);
}

void PointLight::SetIntensity(float intensity)
{
	_intensity = fmax(intensity, 0.0f);
}