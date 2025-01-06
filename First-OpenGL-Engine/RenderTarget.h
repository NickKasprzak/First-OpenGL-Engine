#pragma once
#include <glad/glad.h>
#include <vector>

#include "Texture.h"

class RenderTarget
{
public:
	RenderTarget() = default;
	~RenderTarget() = default;

	bool Initialize(int width, int height, int numColorAttachments, bool hasDepthStencil);
	void Dispose();

	int GetID();
	Texture* GetColorBuffer(unsigned int ID);
	Texture* GetDepthBuffer();

	int GetWidth();
	int GetHeight();
private:
	unsigned int FBO;
	int _width;
	int _height;
	bool _hasDepthStencil;

	// Pool these guys?
	std::vector<Texture> _colorBuffers;
	Texture _depthStencilBuffer;
};