#version 150 core

in vec4 fragmentColor;
in vec2 TexCoord;

uniform sampler2D fragment_texture;

out vec4 color;

void main()
{
	color = texture2D(fragment_texture, TexCoord);
    
}
