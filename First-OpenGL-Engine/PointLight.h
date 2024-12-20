#pragma once
#include <glm/glm.hpp>

// how would i set point light terms based on a radius and intensity value?
class PointLight
{
public:
	PointLight() = default;
	~PointLight() = default;

	float CalcLightRadius();

	glm::vec3 GetPosition();
	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	float GetConstantTerm();
	float GetLinearTerm();
	float GetQuadraticTerm();

	void SetPosition(float position);
	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);
	void SetConstantTerm(float constantTerm);
	void SetLinearTerm(float linearTerm);
	void SetQuadraticTerm(float quadraticTerm);

private:
	glm::vec3 _position = glm::vec3(0.0f);
	glm::vec3 _ambientColor = glm::vec3(0.5f);
	glm::vec3 _diffuseColor = glm::vec3(0.5f);
	glm::vec3 _specularColor = glm::vec3(0.5f);

	float _constantTerm = 1.0f;
	float _linearTerm = 0.1f;
	float _quadraticTerm = 0.032f;
};