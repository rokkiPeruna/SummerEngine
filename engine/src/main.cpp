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

#include <core/Engine.h>

int main(int argc, char *argv[])
{
	se::Engine GameEngine;
	GameEngine.InitializeEngine();
	
	
	
	GameEngine.EngineUpdate();

	return 0;
	
}