#pragma once
#include <vector>
#include <algorithm>

#include "RenderContext.h"
#include "SceneNode.h"

struct RenderData
{
	Mesh* mesh;
	glm::mat4 modelMatrix;
};

class RenderDrawBuffer
{
public:
	void Push(int fullscreenLayer, int viewport, int viewportLayer, unsigned int materialID, RenderData drawData); // typedef these args?
	
	void SortDrawBuffer()
	{
		//std::sort(_drawBuffer.begin(), _drawBuffer.end());
	}

private:
	//std::vector<std::pair<RenderContext, RenderData>> _drawBuffer;
};