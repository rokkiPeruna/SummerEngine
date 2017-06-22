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

#include <core/Engine.h>

#include <managers/Entity.h>
#include <managers/EntityComponentManager.h>

int main(int argc, char *argv[])
{
	se::Engine GameEngine;

	se::EntityComponentManager ecm;
	auto player = ecm.CreateEntity("player");
	auto second = ecm.CreateEntity(player);
	auto third = ecm.CreateEntity(player);
	auto fourth = ecm.CreateEntity(third);
	std::cout << player->name << "  " << second->name << "  " << third->name << fourth->name << std::endl;


	GameEngine.InitializeEngine();
	GameEngine.EngineUpdate();
	

	

	return 0;
	
}