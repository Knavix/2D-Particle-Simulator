#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uOffset;
void main()
{
	vec2 finalPos = aPos + uOffset;
	gl_Position = vec4(finalPos, 0.0, 1.0);
}