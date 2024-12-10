#include "Camera.h"

void Camera::HandleCursorInput(double xPos, double yPos)
{
	if (_firstMouse)
	{
		_lastMouseX = xPos;
		_lastMouseY = yPos;
		_firstMouse = false;
	}

	float xOffset = xPos - _lastMouseX;
	float yOffset = _lastMouseY - yPos;
	_lastMouseX = xPos;
	_lastMouseY = yPos;

	xOffset *= _sensitivity;
	yOffset *= _sensitivity;

	_yaw += xOffset;
	_pitch += yOffset;

	if (_pitch > 89.0f)
	{
		_pitch = 89.0f;
	}
	else if (_pitch < -89.0f)
	{
		_pitch = -89.0f;
	}

	_forward.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_forward.y = sin(glm::radians(_pitch));
	_forward.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_forward = glm::normalize(_forward);

	UpdateViewMatrix();
}

void Camera::HandleKeyboardInput(CameraInput inputType)
{
	float displacement = _speed * Time::GetDeltaTime();

	switch (inputType)
	{
	case FORWARD:
		_pos += displacement * _forward;
		break;
	case BACKWARD:
		_pos -= displacement * _forward;
		break;
	case LEFT:
		_pos -= glm::normalize(glm::cross(_forward, _up)) * displacement;
		break;
	case RIGHT:
		_pos += glm::normalize(glm::cross(_forward, _up)) * displacement;
		break;
	default:
		break;
	}

	UpdateViewMatrix();
}

void Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	_fov = fov;
	_aspectRatio = aspectRatio;
	_nearPlane = nearPlane;
	_farPlane = farPlane;
	_isPerspective = true;
	_projectionMatrix = glm::perspective(glm::radians(_fov), _aspectRatio, _nearPlane, _farPlane);
}

void Camera::SetOrthographic(float top, float bottom, float left, float right)
{
	_top = top;
	_bottom = bottom;
	_left = left;
	_right = right;
	_isPerspective = false;
	_projectionMatrix = glm::ortho(_left, _right, _bottom, _top);
}

glm::mat4 Camera::GetViewMatrix()
{
	return _viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

glm::vec3 Camera::GetPosition()
{
	return _pos;
}

glm::vec3 Camera::GetDirection()
{
	return _forward;
}

void Camera::UpdateViewMatrix()
{
	_viewMatrix = glm::lookAt(_pos, _pos + _forward, _up);
}