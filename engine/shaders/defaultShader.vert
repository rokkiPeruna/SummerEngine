#version 150 core

in vec3 vertexPosition;
in vec4 vertexColor;

out vec3 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 transform;


void main()
{
	
	gl_Position = transform * vec4(vertexPosition, 1.0);

	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
}

