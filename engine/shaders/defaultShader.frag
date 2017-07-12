#version 150 core

//
in vec3 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;


uniform float time;


void main()
{

	
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x * 4.0 + time) + 1.0) * 0.5,
				 fragmentColor.g * (cos(fragmentPosition.y * 4.0 + time) + 1.0) * 0.5,
				 fragmentColor.b * (cos(fragmentPosition.x * 4.0 + time + 1.9) + 1.0) * 0.5,
				 fragmentColor.a);

}