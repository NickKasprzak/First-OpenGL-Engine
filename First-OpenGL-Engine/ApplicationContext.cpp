#include "ApplicationContext.h"

#include <stb/stb_image.h>

#include <iostream>
#include <vector>

#include "Time.h"
#include "TextureLoader.h"
#include "Shader.h"
#include "SceneNode.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "MeshLoader.h"
#include "Primitives.h"
#include "DirectionalLight.h"
#include "PointLight.h"

ApplicationContext* ApplicationContext::_instance = nullptr;

Camera testCamera;
Shader testShader;
Mesh testMesh;
Texture testTexture;
Material testMaterial;
std::vector<SceneNode> testRenderables;
DirectionalLight testDirLight;
RenderTarget testRenderTarget;
std::vector<PointLight> testPointLights;

ApplicationContext* ApplicationContext::Instance()
{
	if (_instance == nullptr)
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

	ShaderManager::Instance()->Initialize();

	// temp camera
	_window.SetCamera(&testCamera);
	testCamera.SetPerspective(45.5f, 800.0f / 600.0f, 0.1f, 100.0f);

	// temp shader
	testShader = *ShaderManager::Instance()->GetShader("GeometryPass");

	// temp again
	Primitives::BuildPrimitiveConstants();

	// temp obj
	MeshLoader meshLoader;
	testMesh = meshLoader.LoadMeshFromPath("C:/Users/AquaB/Downloads/Sphere/sphere.obj");
	//testMesh = meshLoader.LoadMeshFromPath("C:/Users/AquaB/Downloads/Cube/cube.obj");

	TextureLoader textureLoader;
	testTexture = textureLoader.LoadTextureFromPath("C:/Users/AquaB/Downloads/OldSky.png");

	testMaterial.Initialize(&testShader, 0);
	testMaterial.SetTexture("diffuseMap", &testTexture, 1);

	SceneNode testRenderable;
	testRenderable.SetMesh(&testMesh);
	testRenderable.SetMaterial(&testMaterial);
	testRenderables.push_back(testRenderable);

	SceneNode testRenderable2;
	testRenderable2.SetMesh(&Primitives::cube);
	testRenderable2.SetMaterial(&testMaterial);
	testRenderable2.SetPosition(glm::vec3(0, -2.0f, 0));
	testRenderable2.SetScale(glm::vec3(5.0f, 0.25f, 5.0f));
	testRenderables.push_back(testRenderable2);

	PointLight pointLight1;
	pointLight1.SetPosition(glm::vec3(0, 3, 0));
	pointLight1.SetIntensity(1);
	testPointLights.push_back(pointLight1);

	PointLight pointLight2;
	pointLight2.SetPosition(glm::vec3(3, 0, 0));
	pointLight2.SetIntensity(1);
	pointLight2.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	testPointLights.push_back(pointLight2);

	testRenderTarget.Initialize(1024, 1024, 0, true);
	testDirLight.SetShadowMap(testRenderTarget);

	// not temp
	_renderer._gBuffer.Initialize(800, 600);
	_renderer.UpdateScreenSize(glm::vec2(800, 600));
	_renderer.SetCamera(&testCamera);

	return 1;
}

void ApplicationContext::Dispose()
{
	ShaderManager::Instance()->Dispose();
	delete(ShaderManager::Instance());

	glfwTerminate();
}

bool ApplicationContext::Update()
{
	if (_window.ShouldClose()) { return false; }
	Time::Update();
	
	_window.HandleKeyboardInput();

	for (int i = 0; i < testRenderables.size(); i++)
	{
		_renderer.PushMeshDrawCall(0, 0, 0, &testRenderables[i]);
	}
	_renderer.PushDirectionalLight(&testDirLight);
	for (int i = 0; i < testPointLights.size(); i++)
	{
		_renderer.PushPointLight(&testPointLights[i]);
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
		ApplicationContext::Instance()->GetRenderer()->UpdateScreenSize(glm::vec2(width, height));
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