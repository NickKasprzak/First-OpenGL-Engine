#version 330 core

// Default inputs
in vec2 UV;
in vec3 FragPos;
in vec3 Normal;

// Default outputs passed to GBuffer textures using MRT
layout (location = 0) out vec3 GB_Position;
layout (location = 1) out vec3 GB_Diffuse;
layout (location = 2) out vec3 GB_UV;
layout (location = 3) out vec3 GB_Normal;

// Default diffuse/color map uniform
uniform sampler2D diffuseMap;

void main()
{
	GB_Position = FragPos;
	GB_Diffuse = vec3(texture(diffuseMap, UV));
	GB_UV = vec3(UV, 0);
	GB_Normal = normalize(Normal);
}