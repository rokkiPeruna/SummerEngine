#include "PlayerLogic.h"

PlayerLogic::PlayerLogic()
	: GameLogic("PlayerLogic")
	, _timer(0)
{

}

void PlayerLogic::Init()
{
	se::RegisterEventHandle(playerHandler);
}


void PlayerLogic::Update(float deltaTime)
{
	std::cout << "Player Logic has been updated " << std::endl;
	se::GetTransformComponent(m_entityID)->position.x += 0.5f * deltaTime;
	
}

