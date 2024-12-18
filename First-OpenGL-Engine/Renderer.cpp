#include "Renderer.h"
#include "ShaderManager.h"

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

	/*
	* Enable writing to the depth buffer for geometry.
	* Geometry should be the only thing writing to the
	* depth buffer, everything other pass reads from it.
	*/
	glDepthMask(GL_TRUE);
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

	// Do light-specific passes
	DirectionalLightPass();
	PointLightPass();
	SpotlightPass();
}

void Renderer::DirectionalLightPass()
{
	Shader* dirLightShader = ShaderManager::Instance()->GetShader("DirectionalLightPass");
}

void Renderer::PointLightPass()
{

}

void Renderer::SpotlightPass()
{

}