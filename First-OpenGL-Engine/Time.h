#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Time
{
public:
	static void Update()
	{
		float currentFrame = glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;
	}

	static float GetDeltaTime() { return _deltaTime; }
private:
	Time() = default;
	~Time() = default;

	static float _deltaTime;
	static float _lastFrame;
};