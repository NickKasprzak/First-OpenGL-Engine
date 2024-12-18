#include "PointLight.h"

Sphere PointLight::GetLightVolume()
{
	if (_isDirty)
	{
		UpdateLightVolume();
	}

	return _lightVolume;
}

void PointLight::UpdateLightVolume()
{

}