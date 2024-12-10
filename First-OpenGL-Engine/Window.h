#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "SceneNode.h"
#include "Shader.h"

class Window
{
public:
	Window() = default;
	~Window() = default;
	int Initialize();

	void DrawToFramebuffer(SceneNode* renderable, Shader* shader);
	void FlipBuffer();

	void HandleMouseInput(double xPos, double yPos);
	void HandleKeyboardInput();

	void SetCamera(Camera* camera) { _camera = camera; }
	void SetSize(int width, int height);

	bool ShouldClose() { return glfwWindowShouldClose(_window); }

private:
	GLFWwindow* _window = nullptr;
	Camera* _camera = nullptr;
	int _width = 0;
	int _height = 0;
};