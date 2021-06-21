#version 440
layout (location = 0) in vec2 aPos;

int getOne();

void main()
{
	int one = getOne();
	gl_Position = vec4(aPos, 0.0f, 1.0f);
}