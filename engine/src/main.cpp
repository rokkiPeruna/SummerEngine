#include <iostream>
#include <Box2D/Box2D.h>
#include <SDL2/include/SDL_config.h>
#include <SDL2/include/SDL.h>
#include <GLES3/glew.h>

//For memory management
#include <vld.h>

//For debug
#include <Windows.h>
#include <STB/stb_image.h>
#include <glm/glm.hpp>

#include <core/Engine.h>
#include <utility/Time.h>
#include <utility/Clock.h>

int main(int argc, char *argv[])
{
	se::Clock kello;
	se::Engine GameEngine;

	GameEngine.InitializeEngine();
	
	se::Time aika = kello.getElapsedTime();
	std::cout << aika.asMicroSeconds() << std::endl;
	
	Sleep(3000.f);
	return 0;
}