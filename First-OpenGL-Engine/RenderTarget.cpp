#include "RenderTarget.h"
#include <iostream>

bool RenderTarget::Initialize(int width, int height, int numColorAttachments, bool hasDepthStencil)
{
	_width = width;
	_height = height;

	// Create render target's framebuffer
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create and attach color buffer textures
	for (int i = 0; i < numColorAttachments; i++)
	{
		Texture texture;
		texture.SetWrapMode(GL_CLAMP_TO_EDGE);
		texture.SetMinFilter(GL_NEAREST);
		texture.SetMagFilter(GL_NEAREST);
		texture.Generate(_width, _height, GL_RGB32F, GL_RGB, GL_FLOAT, false, 0);

		unsigned int textureID = texture.GetID();
		glFramebufferTexture2D(FBO, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureID, 0);

		_colorBuffers.push_back(texture);
	}

	// Create depth-stencil buffer if it needs one
	if (hasDepthStencil)
	{
		_hasDepthStencil = true;

		Texture dsTexture;
		dsTexture.SetWrapMode(GL_CLAMP_TO_EDGE);
		dsTexture.SetMinFilter(GL_NEAREST);
		dsTexture.SetMagFilter(GL_NEAREST);
		dsTexture.Generate(_width, _height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, false, 0);

		unsigned int dsTextureID = dsTexture.GetID();
		glFramebufferTexture2D(FBO, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, dsTextureID, 0);
		_depthStencilBuffer = dsTexture;
	}

	// Check if the framebuffer was created properly
	if (glCheckFramebufferStatus(FBO) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Failed to load framebuffer." << std::endl;
		return false;
	}

	return true;
}

void RenderTarget::Dispose()
{

}

Texture* RenderTarget::GetColorBuffer(unsigned int ID)
{

}

Texture* RenderTarget::GetDepthBuffer()
{

}