#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

class ApplicationContext
{
public:
	ApplicationContext() = default;
	static ApplicationContext* Instance();
	int Initialize();
	void Dispose();

	bool Update();

private:
	static ApplicationContext* _instance;
	Window _window;
};