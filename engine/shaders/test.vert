#version 150 core

in vec3 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(vertexPosition, 1.0);
	fragmentColor = vec4(0.1, 0.5, 0.8, 1.0);
}