#include "ApplicationContext.h"

#include <stb/stb_image.h>

#include <iostream>
#include <vector>

#include "Time.h"
#include "TextureLoader.h"
#include "Primitives.h"
#include "Shader.h"

ApplicationContext* ApplicationContext::_instance = nullptr;

Camera testCamera;
Shader testShader;
Cube testMesh;
Texture testTexture;
std::vector<SceneNode> testRenderables;

ApplicationContext* ApplicationContext::Instance()
{
	if (_instance == NULL)
	{
		_instance = new ApplicationContext();
	}
	return _instance;
}

int ApplicationContext::Initialize()
{
	glfwInit();

	int winInitialized = _window.Initialize();
	if (winInitialized == -1)
	{
		std::cout << "Failed to create a window." << std::endl;
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Couldn't initialize GLAD." << std::endl;
		return -1;
	}

	_window.SetSize(800, 600);

	stbi_set_flip_vertically_on_load(true);

	// temp camera
	_window.SetCamera(&testCamera);
	testCamera.SetPerspective(45.5f, 800.0f / 600.0f, 0.1f, 100.0f);

	// temp shader
	testShader.LoadProgram("C:/Users/AquaB/Documents/Projects/First-OpenGL-Engine/First-OpenGL-Engine/basicShader.vert",
						   "C:/Users/AquaB/Documents/Projects/First-OpenGL-Engine/First-OpenGL-Engine/basicShader.frag");

	testMesh.BuildCube();

	TextureLoader textureLoader;
	testTexture = textureLoader.LoadTextureFromPath("C:/Users/AquaB/Downloads/OldSky.png");
	testTexture.SetType("diffuseMap");
	testMesh.AddTexture(testTexture);

	SceneNode testRenderable;
	testRenderable.SetMesh(&testMesh);
	testRenderables.push_back(testRenderable);

	return 1;
}

void ApplicationContext::Dispose()
{
	glfwTerminate();
}

bool ApplicationContext::Update()
{
	if (_window.ShouldClose()) { return false; }
	Time::Update();
	
	_window.HandleKeyboardInput();

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < testRenderables.size(); i++)
	{
		_window.DrawToFramebuffer(&(testRenderables[i]), &testShader);
		testRenderables[i].Draw(&testShader);
	}

	glfwPollEvents();
	_window.FlipBuffer();
	return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Window* windowUser = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (windowUser != NULL)
	{
		windowUser->SetSize(width, height);
	}
}

void mouse_input_callback(GLFWwindow* window, double xPos, double yPos)
{
	Window* windowUser = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	if (windowUser != NULL)
	{
		windowUser->HandleMouseInput(xPos, yPos);
	}
}