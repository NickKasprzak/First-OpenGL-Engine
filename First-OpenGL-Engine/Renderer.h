#pragma once
#include <vector>

#include "GBuffer.h"
#include "RenderDrawBuffer.h"
#include "SceneNode.h"
#include "Camera.h"

class Renderer
{
public:
	void SetCamera(Camera* camera);

	void PushRenderDrawCall(int fullscreenLayer, int viewport, int viewportLayer, SceneNode* node);	
	void ProcessRenderCalls();
	void ClearRenderBuffer();

	void GeometryPass();
	void LightingPass();

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

	RenderDrawBuffer _renderBuffer;
	Camera* _camera;

	std::vector<SceneNode*> tempNodes;
};