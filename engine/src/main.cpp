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


class Player : public se::Entity
{
public:
	Player() 
		: se::Entity("player")
		, transform(nullptr)
	{
		transform = se::Entity::AddComponent(&se::CTransform2D());
	}

	std::shared_ptr<se::CTransform2D> transform;
};

int main(int argc, char *argv[])
{
	se::Engine GameEngine;
	GameEngine.InitializeEngine();

	GameEngine.EngineUpdate();
	

	return 0;
	
}