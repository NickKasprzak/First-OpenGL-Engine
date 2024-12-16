#include "Renderer.h"

void Renderer::SetCamera(Camera* camera)
{
	_camera = camera;
}

void Renderer::PushRenderDrawCall(int fullscreenLayer, int viewport, int viewportLayer, SceneNode* node)
{
	tempNodes.push_back(node);
}

void Renderer::ClearRenderBuffer()
{

}

void Renderer::ProcessRenderCalls()
{
	GeometryPass();
	LightingPass();

	tempNodes.clear();
}

void Renderer::GeometryPass()
{
	/*
	* Bind and clear our GBuffer for writing
	* our geometry pass to
	*/
	_gBuffer.BindForWriting();
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

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
}

void Renderer::LightingPass()
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

	// Enable the lighting shader
	// Each light type gets their own shader
	// that gets defined and used independently
	// of materials
}