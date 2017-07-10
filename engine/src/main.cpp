#include <iostream>

//#undef main
//For memory management
//#include <vld.h>
//For debug
#include <Windows.h>
#include <core/Engine.h>



int main(int argc, char *argv[])
{
	se::priv::Engine& GameEngine = se::priv::Engine::Instance();
	GameEngine.InitializeEngine();
	
	
	//se::Entity* player = GameEngine.GetEntityCompMgr()->CreateEntity("player");
	//ecm->AddComponent()
	//ecm->GetTransform2D("player");
	


	GameEngine.EngineUpdate();
	
	return 0;
	
}