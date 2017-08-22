#ifndef SUMMER_ENGINE_GAMELOGIC_H
#define SUMMER_ENGINE_GAMELOGIC_H

///STL includes:
#include <string>

///SE includes:
#include <core/Engine.h>
#include <components/Component.h>
#include <events/Events.h>

#include <systems/AnimationSystem.h>
#include <systems/CollisionSystem.h>
#include <systems/ComponentSystem.h>
#include <systems/GameLogicSystem.h>
#include <systems/TransformSystem.h>
#include <systems/MovementSystem.h>


namespace se
{
class GameLogic
{
public:
	GameLogic(std::string name) 
		: active(false)
		, m_entityID(-1)
		, m_name(name)
	{
		
	}
	virtual ~GameLogic() = default;
	//SE_TODO: Do copy and move


	SEbool active;

	virtual void Init() = 0;

	virtual void Update(SEfloat deltaTime) = 0;

	virtual GameLogic* Create() = 0;

	std::string GetName() const { return m_name; }

	void entityID(SEint id) { m_entityID = id; }
	SEint entityID() { return m_entityID; }


protected:

	SEint m_entityID;
	const std::string m_name;
	
};
}
#endif