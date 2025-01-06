#pragma once
#include <glad/glad.h>
#include <vector>

enum GBufferType
{
	GBUFFER_POSITION,
	GBUFFER_DIFFUSE,
	GBUFFER_UV,
	GBUFFER_NORMAL
};

class GBuffer
{
public:
	GBuffer() = default;
	~GBuffer() = default;

	void Initialize(int width, int height);
	void Dispose();

	void BindForWriting();
	void BindForReading();
	void SetReadTarget(GBufferType targetType);

	std::vector<unsigned int> GetAttribTextures() { return _attribTextures; }
private:
	std::vector<unsigned int> _attribTextures;
	unsigned int _depthTexture;
	unsigned int FBO;

	int _width;
	int _height;
};