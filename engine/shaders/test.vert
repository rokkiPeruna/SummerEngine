#version 150 core

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexTexture;

out vec4 fragmentColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
//   gl_Position = vec4(vertexPosition, 1.0);
	gl_Position = transform * vec4(vertexPosition, 1.0);
	fragmentColor = vertexColor;
    
    TexCoord = vertexTexture;
}