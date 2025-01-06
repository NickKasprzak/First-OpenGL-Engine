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
	std::vector<GLenum> attachments;
	for (int i = 0; i < numColorAttachments; i++)
	{
		Texture texture;
		texture.SetWrapMode(GL_CLAMP_TO_EDGE);
		texture.SetMinFilter(GL_NEAREST);
		texture.SetMagFilter(GL_NEAREST);
		texture.Generate(_width, _height, GL_RGB32F, GL_RGB, GL_FLOAT, false, 0);

		unsigned int textureID = texture.GetID();
		texture.Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureID, 0);
		texture.Unbind();

		_colorBuffers.push_back(texture);
		attachments.push_back(GL_COLOR_ATTACHMENT0 + 1);
	}

	// Set draw buffers
	glDrawBuffers(attachments.size(), attachments.data());

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
		dsTexture.Bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, dsTextureID, 0);
		dsTexture.Unbind();

		_depthStencilBuffer = dsTexture;
	}

	// Check if the framebuffer was created properly
	GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Failed to load framebuffer. " << fboStatus << std::endl;
		return false;
	}

	return true;
}

void RenderTarget::Dispose()
{
	for (int i = 0; i < _colorBuffers.size(); i++)
	{
		_colorBuffers[i].Dispose();
	}
	_colorBuffers.clear();
	
	if (_hasDepthStencil)
	{
		_depthStencilBuffer.Dispose();
		_hasDepthStencil = false;
	}

	glDeleteFramebuffers(1, &FBO);
	FBO = 0;
}

int RenderTarget::GetID()
{
	if (FBO > 0)
	{
		return FBO;
	}

	return -1;
}

Texture* RenderTarget::GetColorBuffer(unsigned int index)
{
	if (index < _colorBuffers.size())
	{
		return &_colorBuffers[index];
	}

	return NULL;
}

Texture* RenderTarget::GetDepthBuffer()
{
	if (_hasDepthStencil)
	{
		return &_depthStencilBuffer;
	}
	return nullptr;
}

int RenderTarget::GetWidth()
{
	return _width;
}

int RenderTarget::GetHeight()
{
	return _height;
}