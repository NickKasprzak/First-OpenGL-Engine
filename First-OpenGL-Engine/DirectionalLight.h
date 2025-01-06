#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RenderTarget.h"

class DirectionalLight
{
public:
	DirectionalLight() = default;
	~DirectionalLight() = default;

	glm::vec3 GetColor();
	glm::vec3 GetDirection();
	// Replace with reference later
	RenderTarget* GetShadowMap();
	glm::mat4 GetLVPMatrix();

	void SetColor(glm::vec3 color);
	void SetDirection(glm::vec3 direction);
	// Replace with reference later
	void SetShadowMap(RenderTarget shadowMap);
	void SetLVPFrustum(glm::vec3 offset, glm::vec4 size, float nearClip, float farClip);

private:
	void _updateLVPMatrix();

	glm::vec3 _color = glm::vec3(0.5f);
	glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	
	// LVP frustum stuff
	// dump all this stuff into a seperate class?
	glm::vec3 _frustumOffset = glm::vec3(100.0f, 100.0f, 100.0f);
	glm::vec4 _frustumSize = glm::vec4(100.0f, 100.0f, 100.0f, 100.0f);
	float _frustumNearClip = 0.1f;
	float _frustumFarClip = 200.0f;
	glm::mat4 _LVPMatrix;

	// Replace with reference later
	RenderTarget _shadowMap;
};