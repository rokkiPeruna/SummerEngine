#version 150 core

in vec2 vertexPosition;
in vec2 textureCoordinates;

void main()
{
	gl_Position = vec4(vertexPosition, 0.0, 1.0);
}