#include "EnemyLogic.h"

EnemyLogic::EnemyLogic()
	: GameLogic("EnemyLogic")
	, _timer(0)
{
	
}

void EnemyLogic::Init()
{
	enemyHandler->SendEvent(se::SE_Event_GameLogicActivated("EnemyLogic", m_entityID));
}

void EnemyLogic::Update(float deltaTime)
{
	
	se::GetTransformComponent(m_entityID)->position.x -= 0.5f * deltaTime;
	se::GetTransformComponent(m_entityID)->rotation += deltaTime;

	if(_timer > 10)
	{
		enemyHandler->SendEvent(se::SE_Event_GameLogicActivated("PlayerLogic", m_entityID));
		_timer = 0;
	}

	_timer += deltaTime;

}