#include "RenderTarget.h"

void RenderTarget::Initialize(int width, int height, int numColorAttachments, bool hasDepthStencil)
{
	glGenFramebuffers(1, &FBO);
}

void RenderTarget::Dispose()
{

}