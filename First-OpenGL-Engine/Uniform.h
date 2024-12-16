#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

enum UniformType
{
	UNIFORM_BOOL,
	UNIFORM_INT,
	UNIFORM_FLOAT,
	UNIFORM_VEC3,
	UNIFORM_MAT3,
	UNIFORM_MAT4
};

struct Uniform
{

};

struct UniformData
{
	UniformType Type;
	union
	{
		bool Bool;
		int Int;
		float Float;
		glm::vec3 Vec3;
		glm::mat3 Mat3;
		glm::mat4 Mat4;
	};
};

struct TextureData
{
	unsigned int Unit;
	Texture* Texture;
};