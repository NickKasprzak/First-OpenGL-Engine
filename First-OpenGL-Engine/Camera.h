#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Time.h"

enum CameraInput
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	NONE,
};

class Camera
{
public:
	Camera() { _updateViewMatrix(); };
	~Camera() {};

	void HandleCursorInput(double xPos, double yPos);
	void HandleKeyboardInput(CameraInput input);

	void SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
	void SetOrthographic(float top, float bottom, float left, float right);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::vec3 GetPosition();
	glm::vec3 GetDirection();

private:
	void _updateViewMatrix();

	glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 _forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
	float _yaw = -90.0f;
	float _pitch = 0.0f;

	// Perspective
	float _fov = 90.0f;
	float _aspectRatio = 800.0f / 600.0f;
	float _nearPlane = 0.1f;
	float _farPlane = 100.0f;

	// Orthographic
	float _top = 0;
	float _bottom = 0;
	float _left = 0;
	float _right = 0;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;

	float _lastMouseX = 800 / 2;
	float _lastMouseY = 600 / 2;
	bool _firstMouse = true;

	float _sensitivity = 0.1f;
	float _speed = 2.5f;

	bool _isPerspective = true;
};