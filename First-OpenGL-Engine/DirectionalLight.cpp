#include "DirectionalLight.h"

#include <iostream>

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
	_direction = direction;
	_updateLVPMatrix();
}

void DirectionalLight::SetShadowMap(RenderTarget shadowMap)
{
	_shadowMap = shadowMap;
}

void DirectionalLight::SetLVPFrustum(float offset, glm::vec4 size, float nearClip, float farClip)
{
	_frustumOffset = offset;
	_frustumSize = size;
	_frustumNearClip = nearClip;
	_frustumFarClip = farClip;
	_updateLVPMatrix();
}

void DirectionalLight::_updateLVPMatrix()
{
	// still wrong. direction looks inversed.
	// does negating it fix?
	glm::vec3 offset = _frustumOffset * glm::normalize(-_direction);
	glm::mat4 view = glm::lookAt(offset, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::ortho(-_frustumSize.x, _frustumSize.y, -_frustumSize.z, _frustumSize.w, _frustumNearClip, _frustumFarClip);
	_LVPMatrix = proj * view;
}