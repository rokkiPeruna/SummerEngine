#ifndef SE_GAMELOGIC_H
#define SE_GAMELOGIC_H

///STL includes:
#include <string>

///SE includes:
#include <core/Engine.h>
#include <components/Component.h>
#include <systems/GameLogicSystem.h>

namespace se
{
class GameLogic
{
public:
	GameLogic(std::string name) 
		: active(false)
		, m_name(name)
	{

	}
	virtual ~GameLogic() = default;
	//SE_TODO: Do copy and move


	SEbool active;

	virtual void Init() = 0;

	virtual void Update(SEfloat deltaTime) = 0;

	std::string GetName() const { return m_name; }

protected:
	const std::string m_name;
};
}
#endif