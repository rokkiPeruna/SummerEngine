#version 150 core

out vec4 color;
uniform vec4 line_color = vec4(1.0);

void main()
{
	color = line_color;
}
