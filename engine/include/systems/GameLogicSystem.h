#ifndef SUMMER_ENGINE_GAME_LOGIC_SYSTEM_H
#define SUMMER_ENGINE_GAME_LOGIC_SYSTEM_H

//include standard library
#include <unordered_map>

//include external

//include se
#include <systems/ComponentSystem.h>
#include <components/CGameLogic.h>
#include <events/Events.h>


namespace se
{

class GameLogic;

CGameLogic* GetGameLogicComponent(SEint index);
void RegisterEventHandle(EventHandler*& eventHandler);

namespace priv
{


class GameLogicSystem : public ComponentSystem
{

	friend CGameLogic* se::GetGameLogicComponent(SEint index);
	friend void se::RegisterEventHandle(EventHandler*& eventHandler);

public:

	///Default constructor
	///1. param engine reference
	GameLogicSystem(Engine& engine_ref);
	
	///Destructor
	~GameLogicSystem();
	
	///Delete copy constructor and assignment operator
	GameLogicSystem(const GameLogicSystem&) = delete;
	void operator=(const GameLogicSystem&) = delete;
	
	///Delete move opeation
	GameLogicSystem(GameLogicSystem&&) = delete;
	void operator=(GameLogicSystem&&) = delete;

	///Initialize system
	void Initialize() override final;

	///Uninitialize system
	void Uninitialize() override final;

	///Update each logic components 'active' logic
	void Update(SEfloat deltaTime) override final;

	///Cleat component container(s)
	void ClearComponentContainers() override final;

	///Is called when new entity is added (or loaded)
	void OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj) override final;

	///Is called when entity is removed
	void OnEntityRemoved(Entity& entity) override final;

	///Is called when this systems component is created
	SEint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	///Is called when this systems component is removed
	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	///Returns plain Component* used in editor function.
	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

	///Assigns pre declared custom game logics to spesific entities.
	void AssingGameLogic(std::string logic_name, CGameLogic& component);

	///Initialize all game logics depsite their activity
	void InitializeGameLogics();
		
private:

	//All possible logic components (all instances components in 'AddLogicToEngine.h')
	std::vector<std::string> m_game_logic_names;

	//All logic components 
	std::vector<CGameLogic> m_cGameLogic;
	
	//Free indices
	std::queue<SEint> m_free_cGameLogic_indices;


	struct _findByValue
	{
		SEint id;
		char* name;

		_findByValue(SEint id) : id(id) {}
		_findByValue(char* name) : name(name) {}
		bool operator() (const CGameLogic& CgameLogic) const
		{
			return CgameLogic.ownerID == id;
		}
	};

};

}//! namespace priv
}//! namespace se

#endif// !SE_GAME_LOGIC_SYSTEM_H