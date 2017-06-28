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
	se::priv::Engine& GameEngine = se::priv::Engine::Instance();
	GameEngine.InitializeEngine();

	auto ecm = GameEngine.GetEntityCompMgr();
	auto p = ecm->CreateEntity("player");
	
	
	//se::Entity* player = GameEngine.GetEntityCompMgr()->CreateEntity("player");
	//ecm->AddComponent()
	//ecm->GetTransform2D("player");
	se::AddTransform2D(p->id, se::CTransform2D(se::Vec2f(1.0f)));
	se::GetTransform2D(p->id);


	GameEngine.EngineUpdate();
	
	return 0;
	
}