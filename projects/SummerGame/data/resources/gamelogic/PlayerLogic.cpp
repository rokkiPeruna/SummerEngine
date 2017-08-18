#include "PlayerLogic.h"

PlayerLogic::PlayerLogic()
	: GameLogic("PlayerLogic")
	, _timer(0)
{

}

void PlayerLogic::Init()
{
	se::RegisterEventHandle(playerHandler);
	playerHandler->SendEvent(se::SE_Event_GameLogicActivated("PlayerLogic", m_entityID));
}

void PlayerLogic::Update(float deltaTime)
{
	se::GetTransformComponent(m_entityID)->position.x += 0.5f * deltaTime;

	if (_timer > 10)
	{
		playerHandler->SendEvent(se::SE_Event_GameLogicActivated("EnemyLogic", m_entityID));
		_timer = 0;
	}
	
	_timer += deltaTime;
}

