#ifndef SUMMERGAME_PLAYERLOGIC_H
#define SUMMERGAME_PLAYERLOGIC_H

///SE includes:
#include <core/GameLogic.h>
#include <events/Events.h>
#include <managers/Keyboard.h>

class PlayerLogic : public se::GameLogic
{
public:

	PlayerLogic()
		: GameLogic("PlayerLogic")
		, kb{}
	{

	}

	void Init() override final
	{
		
	}

	void Update(float deltaTime) override final
	{
		if (kb.GetState(se::KeyboardState::Left))
		{
			
		}
		if (kb.GetState(se::KeyboardState::Rigth))
		{

		}
		if (kb.GetState(se::KeyboardState::Up))
		{

		}
		if (kb.GetState(se::KeyboardState::Down))
		{

		}
	}

private:
	se::Keyboard kb;
};
#endif