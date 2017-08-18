#version 150 core

in vec3 vertexPosition;
in vec4 vertexColor;

uniform mat4 view = mat4(1.0);
uniform mat4 persp = mat4(1.0);

void main()
{
	gl_Position = persp * view * vec4(vertexPosition, 1.0);
	gl_PointSize = 10.0;
	//gl_Position = vec4(vertexPosition, 1.0);
}