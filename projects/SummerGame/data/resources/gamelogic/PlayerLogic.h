#ifndef SUMMERGAME_PLAYERLOGIC_H
#define SUMMERGAME_PLAYERLOGIC_H

#include <core/GameLogic.h>


class PlayerLogic : public se::GameLogic
{
public:

	
	PlayerLogic()
		: GameLogic("PlayerLogic")
		, timer(0)
	{
		
	}

	float timer;
	
	void Init() override final
	{
		std::cout << "Initialize Player" << std::endl;
	}

	void Update(float deltaTime) override final
	{
		se::GetTransformComponent(m_entityID)->position.x += 0.5f * deltaTime;
		std::cout << timer << std::endl;

	}
};
#endif