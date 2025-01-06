#pragma once
#include <vector>

#include "GBuffer.h"
#include "RenderDrawBuffer.h"
#include "SceneNode.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Renderer
{
public:
	void SetCamera(Camera* camera);
	void UpdateScreenSize(glm::vec2 screenSize) { _screenSize = screenSize; }

	void PushMeshDrawCall(int fullscreenLayer, int viewport, int viewportLayer, SceneNode* node);
	void PushDirectionalLight(DirectionalLight* light);
	void PushPointLight(PointLight* light);

	void ProcessRenderCalls();
	void ClearRenderBuffer();

	void GeometryPass();
	void LightingPass();
	void ShadowPass();

	/*
	* Public for now, not sure if we would
	* need one for different viewports
	* 
	* Itd also need to be resized with the window.
	* 
	* Each viewport would also need a camera so that
	* thats another point to the seperation
	*/
	GBuffer _gBuffer;
private:
	void DirectionalLightPass();
	void PointLightPass();
	void SpotlightPass();
	void DirectionalShadowPass();
	void DrawGBufferContents();

	RenderDrawBuffer _renderBuffer;
	Camera* _camera;

	glm::vec2 _screenSize = glm::vec2(800.0f, 600.0f);
	std::vector<SceneNode*> tempNodes;
	DirectionalLight* tempDirLight;
	std::vector<PointLight*> tempPointLights;
};