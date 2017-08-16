#ifndef SUMMERGAME_PLAYERLOGIC_H
#define SUMMERGAME_PLAYERLOGIC_H

#include <gamelogic/GameLogic.h>


class PlayerLogic : public se::GameLogic
{
public:

	PlayerLogic()
		: GameLogic("PlayerLogic")
	{

	}

	void Init() override final
	{
		
	}

	void Update(float deltaTime) override final
	{
		se::GetShapeComponent(m_ownerid);

		se::priv::TransformSystem::TransformableComponents.at(m_ownerid).position.x += 0.5f *deltaTime;
		std::cout << "Do something Player" << std::endl;
	}
};
#endif