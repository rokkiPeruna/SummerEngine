#ifndef SUMMERGAME_PLAYERLOGIC_H
#define SUMMERGAME_PLAYERLOGIC_H

#include <core/GameLogic.h>


class PlayerLogic : public se::GameLogic
{
public:
		
	PlayerLogic();
	
	float timer;
	
	void Init() override final;

	void Update(float deltaTime) override final;

	float _timer;
	se::EventHandler* playerHandler;

};
#endif