#ifndef SUMMERGAME_ENEMYLOGIC_H
#define SUMMERGAME_ENEMYLOGIC_H

#include <core/GameLogic.h>

class EnemyLogic : public se::GameLogic
{
public:

	EnemyLogic()
		: GameLogic("EnemyLogic")
	{

	}

	void Init() override final
	{
		std::cout << "Initialize Enemy" << std::endl;

	}

	void Update(float deltaTime) override final
	{
		se::GetTransformComponent(m_ownerid)->position.x -= 0.5f * deltaTime;
	}
};
#endif