#ifndef SE_MOVEMENTSYSTEM_H
#define SE_MOVEMENTSYSTEM_H


//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CDynamic.h>
#include <managers/EntityManager.h>

namespace se
{
///Getter method for CMovable components
CDynamic* GetDynamicComponent(SEint index);

namespace priv
{
///Brief: MovementSystem handles components that are related to movement, such as CVelocity and CPosition. It has also
///containers for it's related components
class MovementSystem : public ComponentSystem
{
	//Friend getter method for CMovables components
	friend CDynamic* se::GetDynamicComponent(SEint index);

public:
	///Default constructor.
	///1.param: reference to Engine -class
	MovementSystem(Engine& engine_ref);
	///Destructor
	~MovementSystem();
	///Deleted copy constructor and assign operator
	MovementSystem(const MovementSystem&) = delete;
	void operator=(const MovementSystem&) = delete;

	///Initialize system
	void Initialize() override final;

	///Uninitialize system
	void Uninitialize() override final;

	///Run through logic using components as values
	void Update(SEfloat deltaTime) override final;

	///Clear component containers
	void ClearComponentContainers() override final;

	///OnEntityAdded checks if entity has components that need to be builded to this system
	void OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj) override final;

	void OnEntityRemoved(Entity& entity) override final;

	///Creates component to entity and add it to container and json object
	SEint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	///Removes component from entity and container and json object
	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	///Returns plain Component* used in editor function.
	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container);

	static std::vector<SysMessage> Messages;

private:
	///Component containers(vectors) and free index containers(queues)
	std::vector<CDynamic> m_cDynamics;
	std::queue<SEint> m_free_cDynamics_indices;
};
}//namespace priv
}//namespace se


#endif