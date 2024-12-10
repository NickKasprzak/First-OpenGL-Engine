#include "Window.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_input_callback(GLFWwindow* window, double xPos, double yPos);

int Window::Initialize()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(800, 600, "Funny Name :)", NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create a window." << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(_window);

	glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(_window, mouse_input_callback);

	int monitorCount;
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetMonitors(&monitorCount)[0]);
	glfwSetWindowPos(_window, (vidmode->width / 2) - 400, (vidmode->height / 2) - 300);

	return 1;
}

void Window::HandleKeyboardInput()
{
	// tell input manager what inputs were recieved this frame
	// have input manager distribute input events to things registered to it

	// just update camera position stuff here for now though
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, true);
	}

	// Process inputs for camera
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_camera->HandleKeyboardInput(FORWARD);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_camera->HandleKeyboardInput(BACKWARD);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_camera->HandleKeyboardInput(LEFT);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_camera->HandleKeyboardInput(RIGHT);
}

void Window::HandleMouseInput(double xPos, double yPos)
{
	// same deal as keyboard input

	// just update camera orientation stuff here for now
	_camera->HandleCursorInput(xPos, yPos);
}

void Window::DrawToFramebuffer(SceneNode* renderable, Shader* shader)
{
	shader->Use();
	shader->SetMat4Uniform("view", _camera->GetViewMatrix());
	shader->SetVec3Uniform("viewPos", _camera->GetPosition());
	shader->SetMat4Uniform("projection", _camera->GetProjectionMatrix());

	// do renderables draw call stuff
	renderable->Draw(shader);
}

void Window::FlipBuffer()
{
	glfwSwapBuffers(_window);
}

void Window::SetSize(int width, int height)
{
	_width = width;
	_height = height;
	glViewport(0, 0, _width, _height);
}