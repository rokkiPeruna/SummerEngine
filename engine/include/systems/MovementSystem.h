#ifndef SE_MOVEMENTSYSTEM_H
#define SE_MOVEMENTSYSTEM_H


//SE includes:
#include <systems/ComponentSystem.h>

#include <components/CMovable.h>

#include <components/CPosition.h>
#include <components/CVelocity.h>
#include <components/CAcceleration.h>

namespace se
{
///Getter method for CMovables components
std::vector<CMovable>* GetMovablesComponent(SEint index);

namespace priv
{
///Brief: MovementSystem handles components that are related to movement, such as CVelocity and CPosition. It has also
///containers for it's related components
class MovementSystem : public ComponentSystem
{
	//Friend getter method for CMovables components
	friend std::vector<CMovable>* se::GetMovablesComponent(SEint index);

public:
	///Default constructor
	MovementSystem();
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
	void OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj) override final;

	void OnEntityRemoved(Entity& e) override final;


	//EDITOR METHODS

	///Creates component to entity and add it to container and json object
	SEuint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj) override final;

	///Removes component from entity and container and json object
	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj) override final;

	///Modifies component from entity
	Component* ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator* component_obj);

private:
	///Component containers(vectors) and free index containers(queues)
	std::vector<CMovable> m_cMovables;
	std::queue<SEint> m_free_cMovables_indices;

	std::vector<CPosition> m_cpositions;
	std::queue<SEint> m_free_cposition_indices;
	std::vector<CVelocity> m_cvelocities;
	std::queue<SEint> m_free_cvelocity_indices;
	std::vector<CAcceleration> m_caccelerations;
	std::queue<SEint> m_free_cacceleration_indices;

};
}//namespace priv
}//namespace se


#endif