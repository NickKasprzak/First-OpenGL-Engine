#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Renderer.h"

class ApplicationContext
{
public:
	ApplicationContext() = default;
	~ApplicationContext() = default;

	static ApplicationContext* Instance();
	int Initialize();
	void Dispose();

	bool Update();

	Window* GetWindow() { return &_window; }
	Renderer* GetRenderer() { return &_renderer; }

private:
	static ApplicationContext* _instance;
	Window _window;
	Renderer _renderer;
};