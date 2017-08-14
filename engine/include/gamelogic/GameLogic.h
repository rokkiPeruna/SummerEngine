#ifndef SE_GAMELOGIC_H
#define SE_GAMELOGIC_H

///SE includes:
#include <core/Engine.h>
#include <components/Component.h>


namespace se
{
class GameLogic
{
public:
	GameLogic() : active(false)
	{
	
	}
	virtual ~GameLogic() = default;
	//SE_TODO: Do copy and move


	SEbool active;

	virtual void Init() = 0;

	virtual void Update(SEfloat deltaTime) = 0;
};
}
#endif