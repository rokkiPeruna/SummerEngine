#ifndef SUMMER_ENGINE_ADDLOGICTOENGINE_H
#define SUMMER_ENGINE_ADDLOGICTOENGINE_H

///Include all new game logic classes here
///and add them to GameLogicInstances -struct.
///Remember to also initialize with name and possible other values

#include "PlayerLogic.h"
#include "EnemyLogic.h"

#include <Windows.h>

namespace se
{
namespace priv
{


//typedef GameLogic* (*CreateLogicFunction)(void);
//GameLogic* (*CreateLogicFunction)();

//typedef GameLogic* (__stdcall *CreateLogicFunction)(void);


class LogicsFactory
{
public:
	
	~LogicsFactory() { m_factoryMap.clear(); }
	
	static LogicsFactory *GetInstance()
	{
		static LogicsFactory instance;
		return &instance;
	}

	void Register(const std::string& logic_name, GameLogic* type )
	{
		m_factoryMap[logic_name] = type->Create();
	}

	GameLogic* CreateLogic(const std::string& logic_name)
	{
		std::map<std::string, GameLogic*>::iterator itr = m_factoryMap.find(logic_name);
		
		if (itr != m_factoryMap.end())
		{
			Register(logic_name, itr->second->Create());
			auto tmp = itr->second;
			return tmp;
		}
		return nullptr;
	};
	
	std::map<std::string, GameLogic*> m_factoryMap;

private:

	LogicsFactory(const LogicsFactory&) = delete;
	void operator=(const LogicsFactory&) = delete;



	LogicsFactory()
	{
		Register("PlayerLogic", new PlayerLogic);
	};


};




//static std::vector<GameLogic*>GameLogicInstances ///Memory is freed in GameLogicSystem!
//{
//	new PlayerLogic,
//	new EnemyLogic
//	///New logic here, remember comma!!
//
//};

}//namespace priv
}//namespace se

#endif