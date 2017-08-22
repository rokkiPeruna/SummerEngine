#include "PlayerLogic.h"

PlayerLogic::PlayerLogic()
	: GameLogic("PlayerLogic")
	, _timer(0)
{

}

void PlayerLogic::Init()
{
	se::RegisterEventHandle(playerHandler);
}


void PlayerLogic::Update(SEfloat deltaTime)
{
	//Update camera's position
	auto& myPos = se::GetTransformComponent(m_entityID)->position;
	playerHandler->SendEvent(se::SE_Cmd_ChangeCameraPos(se::Vec3f(myPos.x, myPos.y, 10.f)));

	//Move player rigth if rigth arrow is pressed
	if (keyboard.GetState(se::KeyboardState::Rigth))
	{
		playerHandler->SendEvent(se::SE_Event_EntityPositionChanged(m_entityID, { 2.0f * deltaTime, 0.0f, 0.0f }));
		playerHandler->SendEvent(se::SE_Cmd_ChangeAnimation("player_running_rigth", m_entityID));
	}

	//Move player left if left arrow is pressed
	if (keyboard.GetState(se::KeyboardState::Left))
	{
		playerHandler->SendEvent(se::SE_Event_EntityPositionChanged(m_entityID, { -2.0f * deltaTime, 0.0f, 0.0f }));
		playerHandler->SendEvent(se::SE_Cmd_ChangeAnimation("player_running_left", m_entityID));
	}

	//Move player up if up arrow is pressed
	if (keyboard.GetState(se::KeyboardState::Up))
	{
		playerHandler->SendEvent(se::SE_Event_EntityPositionChanged(m_entityID, { 0.0f, 2.0f * deltaTime, 0.0f }));
		playerHandler->SendEvent(se::SE_Cmd_ChangeAnimation("player_running_up", m_entityID));
	}

	//Move player down if down is pressed
	if (keyboard.GetState(se::KeyboardState::Down))
	{
		playerHandler->SendEvent(se::SE_Event_EntityPositionChanged(m_entityID, { 0.0f, -2.0f * deltaTime, 0.0f }));
		playerHandler->SendEvent(se::SE_Cmd_ChangeAnimation("player_running_down", m_entityID));
	}

}

