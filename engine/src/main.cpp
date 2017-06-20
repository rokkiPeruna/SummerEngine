#include <iostream>
#include <Box2D/Box2D.h>
#include <SDL2/include/SDL_config.h>
#include <SDL2/include/SDL.h>
//#undef main

//For memory management
#include <vld.h>

//For debug
#include <Windows.h>
#include <STB/stb_image.h>
#include <glm/glm.hpp>
#include <OpenGL/GLES3/gl3.h>
#include <OpenGL/GLES3/gl3platform.h>
#include <OpenGL/EGL/egl.h>

int main(int argc, char *argv[])
{
	SDL_Init(SDL_VIDEO_OPENGL_ES2);

	glm::mat4 keijo = glm::inverse(glm::transpose(glm::mat4(5.0)));
	GLboolean matti = true;
	GLint64 simo = 100;
	b2CircleShape shape;
	Sleep(3000.f);
	return 0;
}