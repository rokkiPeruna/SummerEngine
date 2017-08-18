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
		se::SetActive(m_ownerid, m_name);
	}

	void Update(float deltaTime) override final
	{
		se::GetTransformComponent(m_ownerid)->position.x += 0.5f * deltaTime;
		std::cout << timer << std::endl;
				
		if (timer > 10)
		{
			se::SetActive(m_ownerid, "EnemyLogic");
		}
		
		timer += 0.1;





	}
};
#endif