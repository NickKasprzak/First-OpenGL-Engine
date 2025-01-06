#version 330 core

// Model data
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 LVP;

// Draw the model using the LVP matrix
void main()
{
	gl_Position = LVP * model * vec4(aPos, 1.0f);
}