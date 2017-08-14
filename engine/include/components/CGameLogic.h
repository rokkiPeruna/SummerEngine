#ifndef SE_CGAMELOGIC_H
#define SE_CGAMELOGIC_H

///STL includes:
#include <vector>
#include <string>

///SE includes:
#include <components/Component.h>
#include <gamelogic/GameLogic.h>

namespace se
{
///Brief: CGameLogic component has container which holds function pointers/lambdas/other
///that define entity behaviour in context of the game logic.
class CGameLogic : public Component
{
public:
	CGameLogic() : Component(COMPONENT_TYPE::FAULTY_TYPE) 
	{
		logics.emplace_back(new PlayerLogic());
	}

	std::vector<GameLogic*> logics; //Run-time-only value. Initialized to empty vector.

	std::vector<std::string> logic_class_names;


	
};

}//namespace se

#endif