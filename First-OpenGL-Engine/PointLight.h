#pragma once
#include <glm/glm.hpp>

class PointLight
{
public:
	PointLight() = default;
	~PointLight() = default;

	glm::vec3 GetPosition();
	glm::vec3 GetColor();
	float GetRadius();
	float GetIntensity();

	void SetPosition(glm::vec3 position);
	void SetColor(glm::vec3 color);
	void SetRadius(float radius);
	void SetIntensity(float intensity);

private:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::vec3 _color = glm::vec3(0.5f);
	float _radius = 5.0f;
	float _intensity = 1.0f;
};