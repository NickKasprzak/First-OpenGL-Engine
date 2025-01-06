#include "DirectionalLight.h"

glm::vec3 DirectionalLight::GetColor()
{ 
	return _color;
}

glm::vec3 DirectionalLight::GetDirection()
{ 
	return _direction;
}

RenderTarget* DirectionalLight::GetShadowMap()
{
	return &_shadowMap;
}

glm::mat4 DirectionalLight::GetLVPMatrix()
{
	return _LVPMatrix;
}

void DirectionalLight::SetColor(glm::vec3 color)
{
	_color = glm::clamp(color, glm::vec3(0.0f), glm::vec3(1.0f));
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	_direction.x = fmod(direction.x, 360.0f);
	_direction.y = fmod(direction.y, 360.0f);
	_direction.z = fmod(direction.z, 360.0f);
	_updateLVPMatrix();
}

void DirectionalLight::SetShadowMap(RenderTarget shadowMap)
{
	_shadowMap = shadowMap;
}

void DirectionalLight::SetLVPFrustum(glm::vec3 offset, glm::vec4 size, float nearClip, float farClip)
{
	_frustumOffset = offset;
	_frustumSize = size;
	_frustumNearClip = nearClip;
	_frustumFarClip = farClip;
	_updateLVPMatrix();
}

void DirectionalLight::_updateLVPMatrix()
{
	glm::mat4 view = glm::lookAt(_frustumOffset * _direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::ortho(_frustumSize.x, _frustumSize.y, _frustumSize.z, _frustumSize.w, _frustumNearClip, _frustumFarClip);
	_LVPMatrix = proj * view;
}