#ifndef SUMMERGAME_ENEMYLOGIC_H
#define SUMMERGAME_ENEMYLOGIC_H

#include <gamelogic/GameLogic.h>

class EnemyLogic : public se::GameLogic
{
public:

	EnemyLogic()
		: GameLogic("EnemyLogic")
	{

	}

	void Init() override final
	{

	}

	void Update(float deltaTime) override final
	{
		se::GetShapeComponent(m_ownerid);

		se::priv::TransformSystem::TransformableComponents.at(m_ownerid).position.x -= 0.5f *deltaTime;
		std::cout << "Do something Enemy" << std::endl;
	}
};
#endif