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
	
	
	playerHandler->SendEvent(se::SE_Event_EntityPositionChanged(m_entityID, { 0.5 * deltaTime, 0.0f, 0.0f }));
	
	
}

