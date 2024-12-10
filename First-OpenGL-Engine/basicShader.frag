#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D diffuseMap1;

void main()
{
	FragColor = vec4(texture(diffuseMap1, UV));
}