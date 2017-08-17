#ifndef SE_ADDLOGICTOENGINE_H
#define SE_ADDLOGICTOENGINE_H

///Include all new game logic classes here
///and add them to GameLogicInstances -struct.
///Remember to also initialize with name and possible other values
#include "PlayerLogic.h"
#include "EnemyLogic.h"

namespace se
{
namespace priv
{
static std::vector<GameLogic*>GameLogicInstances ///Memory is freed in GameLogicSystem!
{
	new PlayerLogic,
	new EnemyLogic
	///New logic here, remember comma!!

};

}//namespace priv
}//namespace se

#endif