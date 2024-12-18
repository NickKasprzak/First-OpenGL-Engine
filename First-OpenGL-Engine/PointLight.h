#pragma once

#include "Primitives.h"

// how should this exist in worldspace
// scenenode or its own thing?
class PointLight
{
public:

	Sphere GetLightVolume();

private:
	void UpdateLightVolume();

	Sphere _lightVolume;
	bool _isDirty = false;
};