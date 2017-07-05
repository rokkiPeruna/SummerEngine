#version 150 core

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

void main()
{
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
	fragmentColor = vertexColor;
}
