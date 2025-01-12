#version 330 core

// We only draw the light volume here like we did with the light passes.
// Pretty much all the shadow stuff is done in the fragment shader.

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}