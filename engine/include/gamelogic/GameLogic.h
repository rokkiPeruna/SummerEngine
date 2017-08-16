#ifndef SE_GAMELOGIC_H
#define SE_GAMELOGIC_H

///STL includes:
#include <string>

///SE includes:
#include <core/Engine.h>
#include <components/Component.h>

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
		, m_ownerid(-1)
		, m_name(name)
	{

	}
	virtual ~GameLogic() = default;
	//SE_TODO: Do copy and move


	SEbool active;

	virtual void Init() = 0;

	virtual void Update(SEfloat deltaTime) = 0;

	std::string GetName() const { return m_name; }

	void ownerID(SEint id) { m_ownerid = id; }
	SEint ownerID() { return m_ownerid; }

protected:

	SEint m_ownerid;
	const std::string m_name;
};
}
#endif