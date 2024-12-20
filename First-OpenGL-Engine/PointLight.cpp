#include "PointLight.h"

float PointLight::CalcLightRadius()
{
	return 0;
}

glm::vec3 PointLight::GetPosition()
{
	return _position;
}

glm::vec3 PointLight::GetAmbient()
{
	return _ambientColor;
}

glm::vec3 PointLight::GetDiffuse()
{
	return _diffuseColor;
}
glm::vec3 PointLight::GetSpecular()
{
	return _specularColor;
}

float PointLight::GetConstantTerm()
{
	return _constantTerm;
}

float PointLight::GetLinearTerm()
{
	return _linearTerm;
}

float PointLight::GetQuadraticTerm()
{
	return _quadraticTerm;
}