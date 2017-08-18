#ifndef SUMMERGAME_ENEMYLOGIC_H
#define SUMMERGAME_ENEMYLOGIC_H
//
#include <core/GameLogic.h>
#include <iostream>


class EnemyLogic : public se::GameLogic
{
public:

	EnemyLogic();

	void Init() override final;
	
	void Update(float deltaTime) override final;

private:

	se::EventHandler* enemyHandler;
	float _timer;

};
#endif