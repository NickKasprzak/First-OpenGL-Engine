#include "GBuffer.h"

void GBuffer::Initialize(int width, int height)
{
	// Generate framebuffer
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
	
	// Generate textures
	_attribTextures.resize(4);
	glGenTextures(4, &_attribTextures[0]);
	glGenTextures(1, &_depthTexture);

	/*
	* Defines our vertex attribute textures and
	* attaches them to our framebuffer as color
	* attachments
	*/
	for (int i = 0; i < _attribTextures.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _attribTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, _attribTextures[i], 0);
	}

	/*
	* Defines our depth texture and attaches it
	* to our framebuffer as its depth attachment
	*/
	glBindTexture(GL_TEXTURE_2D, _depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);

	/*
	* Specify that we want to draw the results
	* of the fragment shader into its first
	* four color attachments.
	* 
	* These correspond to the four textures we
	* generated and bound above, placing the
	* fragment shader output in the geometry
	* pass into them.
	*/
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, drawBuffers);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::Dispose()
{

}

void GBuffer::BindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, FBO);
}

void GBuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}

void GBuffer::SetReadTarget(GBufferType type)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
}