#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uOffset;
uniform  float uScale;
void main()
{
	vec2 finalPos = aPos * uScale + uOffset;
	gl_Position = vec4(finalPos, 0.0, 1.0);
}