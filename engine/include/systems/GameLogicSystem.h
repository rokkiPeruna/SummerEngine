#ifndef SE_GAME_LOGIC_SYSTEM_H
#define SE_GAME_LOGIC_SYSTEM_H

//include standard library
#include <unordered_map>

//include external

//include se
#include <systems/ComponentSystem.h>
#include <components/CGameLogic.h>

namespace se
{
namespace priv
{

class Engine;

class GameLogicSystem : public ComponentSystem
{

public:
	
	GameLogicSystem(Engine& engine_ref);
	~GameLogicSystem();
	GameLogicSystem(const GameLogicSystem&) = delete;
	void operator=(const GameLogicSystem&) = delete;
	GameLogicSystem(GameLogicSystem&&) = delete;
	void operator=(GameLogicSystem&&) = delete;

	void Initialize() override final;

	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void ClearComponentContainers() override final;
	
	void OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj) override final;

	void OnEntityRemoved(Entity& entity) override final;

	SEint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

	void AssingGameLogic(std::string logic_name, CGameLogic& component);

private:

	std::vector<std::string> m_game_logic_names;


	std::vector<CGameLogic> m_cGameLogic;
	std::queue<SEint> m_free_cGameLogic_indices;
};

}//! namespace priv
}//! namespace se

#endif// !SE_GAME_LOGIC_SYSTEM_H