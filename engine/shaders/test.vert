#version 150 core

in vec3 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

uniform mat4 transform;

void main()
{
    gl_Position = vec4(vertexPosition, 1.0);
//	gl_Position = transform * vec4(vertexPosition, 1.0);
	fragmentColor = vertexColor;
}