#include "Renderer.h"
#include "ShaderManager.h"

#include "Primitives.h"

void Renderer::SetCamera(Camera* camera)
{
	_camera = camera;
}

void Renderer::PushMeshDrawCall(int fullscreenLayer, int viewport, int viewportLayer, SceneNode* node)
{
	tempNodes.push_back(node);
}

void Renderer::PushDirectionalLight(DirectionalLight* light)
{
	if (tempDirLight == nullptr)
	{
		tempDirLight = light;
	}
}

void Renderer::PushPointLight(PointLight* light)
{
	tempPointLights.push_back(light);
}

void Renderer::ClearRenderBuffer()
{

}

void Renderer::ProcessRenderCalls()
{
	GeometryPass();
	LightingPass();
	//DrawGBufferContents();
	

	tempNodes.clear();
	tempDirLight = nullptr;
	tempPointLights.clear();
}

void Renderer::GeometryPass()
{
	/*
	* Bind and clear our GBuffer for writing
	* our geometry pass to
	*/
	_gBuffer.BindForWriting();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*
	* Enable writing to the depth buffer for geometry.
	* Geometry should be the only thing writing to the
	* depth buffer, everything other pass reads from it.
	*/
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Also disable blending, it isn't needed here apparently (...really? What about transparency?)
	glDisable(GL_BLEND);

	/*
	* Draw each object using their respective materials.
	* Shader used should have the proper entry and exit
	* points to properly draw their geometry and give the
	* pass the neccessary data it needs to fill the GBuffer.
	*/
	for (int i = 0; i < tempNodes.size(); i++)
	{
		Mesh* mesh = tempNodes[i]->_mesh;
		Material* mat = tempNodes[i]->_material;
		Shader* shader = mat->GetShader();

		mat->UseShader();

		// Defaults that get set independent of the material uniforms
		// View and Projection would ideally get once in a batched call by shader
		shader->SetMat4Uniform("model", tempNodes[i]->_modelMatrix);
		shader->SetMat4Uniform("view", _camera->GetViewMatrix());
		shader->SetMat4Uniform("projection", _camera->GetProjectionMatrix());

		// Bind all material textures
		std::map<std::string, TextureData>* textures = mat->GetAllTextures();
		for (auto it = textures->begin(); it != textures->end(); it++)
		{
			it->second.Texture->Bind(it->second.Unit);
		}

		// Bind all material specific uniforms
		std::map<std::string, UniformData>* uniforms = mat->GetAllUniforms();


		// Draw the object to the GBuffer
		mesh->Draw();
	}

	// Disable depth testing
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
}

void Renderer::LightingPass()
{
	// Switch back to the default buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	* Enable blending for the lighting pass so
	* we can combine the results of each light
	* pass. We ensure blending is just adding
	* values and ensuring they aren't modified
	* beforehand.
	*/
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	/*
	* Bind our GBuffer for reading and clear
	* the color buffer
	*/
	_gBuffer.BindForReading();
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Do light-specific passes
	if (tempDirLight != nullptr)
	{
		DirectionalLightPass();
	}

	if (!tempPointLights.empty())
	{
		PointLightPass();
	}

	SpotlightPass();
}

void Renderer::DirectionalLightPass()
{
	Shader* dirLightShader = ShaderManager::Instance()->GetShader("DirectionalLightPass");

	dirLightShader->Use();

	/*
	* Bind each of the GBuffer's textures to their corresponding units
	* The enums used for the GBuffer's textures should always map directly
	* to the texture units they correspond to.
	*/
	dirLightShader->SetIntUniform("GB_Position", GBUFFER_POSITION);
	dirLightShader->SetIntUniform("GB_Diffuse", GBUFFER_DIFFUSE);
	dirLightShader->SetIntUniform("GB_UV", GBUFFER_UV);
	dirLightShader->SetIntUniform("GB_Normal", GBUFFER_NORMAL);

	// Set MVP matrix to an identity
	glm::mat4 identity = glm::mat4(1.0f);
	dirLightShader->SetMat4Uniform("model", identity);
	dirLightShader->SetMat4Uniform("view", identity);
	dirLightShader->SetMat4Uniform("projection", identity);

	// Set light uniforms
	dirLightShader->SetVec3Uniform("lightColor", tempDirLight->GetColor());
	dirLightShader->SetVec3Uniform("lightDirection", tempDirLight->GetDirection());

	// Set other uniforms
	dirLightShader->SetVec3Uniform("viewPosition", _camera->GetPosition());
	dirLightShader->SetVec2Uniform("screenSize", _screenSize);

	Primitives::quad.Draw();
}

void Renderer::PointLightPass()
{
	// Enable face culling and cull front faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	Shader* pointLightShader = ShaderManager::Instance()->GetShader("PointLightPass");
	pointLightShader->Use();

	// Bind GBuffer contents
	pointLightShader->SetIntUniform("GB_Position", GBUFFER_POSITION);
	pointLightShader->SetIntUniform("GB_Diffuse", GBUFFER_DIFFUSE);
	pointLightShader->SetIntUniform("GB_UV", GBUFFER_UV);
	pointLightShader->SetIntUniform("GB_Normal", GBUFFER_NORMAL);

	// Bind view and projection matrices
	pointLightShader->SetMat4Uniform("view", _camera->GetViewMatrix());
	pointLightShader->SetMat4Uniform("projection", _camera->GetProjectionMatrix());

	// Bind other stuff
	pointLightShader->SetVec3Uniform("viewPosition", _camera->GetPosition());
	pointLightShader->SetVec2Uniform("screenSize", _screenSize);

	// Bind and draw each point light
	for (int i = 0; i < tempPointLights.size(); i++)
	{
		PointLight* light = tempPointLights[i];
		glm::vec3 position = light->GetPosition();
		float scale = light->GetRadius();
		
		glm::mat4 model(1.0f);
		model = glm::translate(model, position);
		model = glm::scale(model, glm::vec3(scale));
		pointLightShader->SetMat4Uniform("model", model);

		pointLightShader->SetVec3Uniform("lightPosition", position);
		pointLightShader->SetVec3Uniform("lightColor", light->GetColor());
		pointLightShader->SetFloatUniform("radius", light->GetRadius());
		pointLightShader->SetFloatUniform("intensity", light->GetIntensity());

		Primitives::sphere.Draw();
	}

	// Disable face culling
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Renderer::SpotlightPass()
{

}

void Renderer::DrawGBufferContents()
{
	// Restore and clear our default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind our GBuffer for reading
	_gBuffer.BindForReading();

	/*
	* Read from and blit each texture in the GBuffer
	* to the screen using BlitFramebuffer, copying
	* the pixel contents of each texture to the
	* specified space on the screen.
	*
	* The first 8 arguments specify where the texture
	* should be sampled and draw, while the 9th argument
	* specifies what buffer should be read from and the
	* 10th argument specifies scaling of the copied data.
	*/
	GLsizei HalfWidth = (GLsizei)(800.0f / 2.0f);
	GLsizei HalfHeight = (GLsizei)(600.0f / 2.0f);
	_gBuffer.SetReadTarget(GBUFFER_POSITION);
	glBlitFramebuffer(0, 0, 800, 600, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	_gBuffer.SetReadTarget(GBUFFER_DIFFUSE);
	glBlitFramebuffer(0, 0, 800, 600, 0, HalfHeight, HalfWidth, 600, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	_gBuffer.SetReadTarget(GBUFFER_NORMAL);
	glBlitFramebuffer(0, 0, 800, 600, HalfWidth, HalfHeight, 800, 600, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	_gBuffer.SetReadTarget(GBUFFER_UV);
	glBlitFramebuffer(0, 0, 800, 600, HalfWidth, 0, 800, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}