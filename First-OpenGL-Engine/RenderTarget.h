#pragma once
#include <glad/glad.h>

#include "Texture.h"

class RenderTarget
{
public:
	RenderTarget() = default;
	~RenderTarget() = default;

	void Initialize(int width, int height, int numColorAttachments, bool hasDepthStencil);
	void Dispose();

	Texture* GetColorAttachment(unsigned int colorAttachmentID);
private:
	unsigned int FBO;

	// Pool textures later?
	
};