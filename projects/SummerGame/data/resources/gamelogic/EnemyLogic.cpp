#include "EnemyLogic.h"

EnemyLogic::EnemyLogic()
	: GameLogic("EnemyLogic")
{
	
}

void EnemyLogic::Init()
{
	se::RegisterEventHandle(enemyHandler);
	

	std::cout << "Hello from enemy cpp " << std::endl;
}

void EnemyLogic::Update(float deltaTime)
{
	char nimi[32]{ "EnemyLogic" };
	enemyHandler->SendEvent(se::SE_Event_GameLogicActivated(nimi, m_entityID));
}