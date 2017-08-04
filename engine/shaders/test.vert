#version 150 core

in vec3 vertexPosition;
in vec4 vertexColor;
in vec2 vertexTexture;

out vec4 fragmentColor;
out vec2 TexCoord;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 persp = mat4(1.0);

void main()
{

	gl_Position = persp * view * model * vec4(vertexPosition, 1.0);
	
	fragmentColor = vertexColor;
    
    TexCoord = vertexTexture;
}