#include "ApplicationContext.h"

#include <stb/stb_image.h>

#include <iostream>
#include <vector>

#include "Time.h"
#include "TextureLoader.h"
#include "Primitives.h"
#include "Shader.h"
#include "SceneNode.h"
#include "Camera.h"

ApplicationContext* ApplicationContext::_instance = nullptr;

Camera testCamera;
Shader testShader;
Cube testMesh;
Texture testTexture;
Material testMaterial;
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
	testShader.LoadProgram("C:/Users/AquaB/Documents/Projects/First-OpenGL-Engine/First-OpenGL-Engine/geometryPass.vert",
						   "C:/Users/AquaB/Documents/Projects/First-OpenGL-Engine/First-OpenGL-Engine/geometryPass.frag");

	// temp obj
	testMesh.BuildCube();

	TextureLoader textureLoader;
	testTexture = textureLoader.LoadTextureFromPath("C:/Users/AquaB/Downloads/OldSky.png");
	testTexture.SetType("diffuseMap");

	testMaterial.Initialize(&testShader, 0);
	testMaterial.SetTexture("diffuseMap", &testTexture, 1);

	SceneNode testRenderable;
	testRenderable.SetMesh(&testMesh);
	testRenderable.SetMaterial(&testMaterial);
	testRenderables.push_back(testRenderable);

	_renderer._gBuffer.Initialize(800, 600);
	_renderer.SetCamera(&testCamera);

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

	for (int i = 0; i < testRenderables.size(); i++)
	{
		_renderer.PushRenderDrawCall(0, 0, 0, &testRenderables[i]);
	}
	_renderer.ProcessRenderCalls();
	_renderer.ClearRenderBuffer();

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