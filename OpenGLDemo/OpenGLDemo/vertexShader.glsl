#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexcoord;

out vec3 ourPosition;
out vec3 ourColor;
out vec2 outTexcoord;

void main()
{
	ourPosition = aPos;
	ourColor = aColor;
	outTexcoord = vec2(aTexcoord.x, aTexcoord.y * -1.f);
	gl_Position = vec4(aPos, 1.0);
	
}