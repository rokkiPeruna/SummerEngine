#ifndef SUMMERGAME_PLAYERLOGIC_H
#define SUMMERGAME_PLAYERLOGIC_H

#include <core/GameLogic.h>
#include <managers/Keyboard.h>


class PlayerLogic : public se::GameLogic
{
public:
		
	PlayerLogic();
		
	void Init() override final;

	void Update(float deltaTime) override final;

	GameLogic* Create() 
	{ 
		GameLogic* result =	new PlayerLogic; 
		return result;
	}


	se::EventHandler playerHandler;
	se::Keyboard keyboard;
	float _timer;

};
#endif