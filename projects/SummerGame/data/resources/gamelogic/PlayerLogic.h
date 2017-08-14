#ifndef SUMMERGAME_PLAYERLOGIC_H
#define SUMMERGAME_PLAYERLOGIC_H

#include <gamelogic/GameLogic.h>

class PlayerLogic : public se::GameLogic
{
public:
	PlayerLogic()
	{

	}

	void Init() override final
	{

	}

	void Update(SEfloat deltaTime) override final
	{
		std::cout << "Do something" << std::endl;

	}
};
#endif