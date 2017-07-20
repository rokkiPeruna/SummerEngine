#ifndef SE_POSITIONSYSTEM_H
#define SE_POSITIONSYSTEM_H

//SE includes
#include <systems/ComponentSystem.h>
#include <components/CPosition.h>

namespace se
{
namespace priv
{
///Brief: PositionSystem handles CPosition components. Since position components are used through out different systems,
///PositionSystem reveals it's component container to public access as static. 
///Because entities are tightly coupled with CPosition components (every entity has one), CPosition components
///are arranged in a way that ensures that CPosition component's index in container is the same as it's owner's id.
///This enables easy search for entity's position: PositionComponents.at(myComponent.ownerID) returns a reference to correct CPosition component.
///Downside for this is that PositionComponent container is partly handled in EntityManager. EntityManager reserves enough space for container
///to fit all scene's entities' CPositionComponents plus some extra. See EntityManager.cpp InitWithNewScene for details.
class PositionSystem : public ComponentSystem
{
public:
	///Default constructor
	PositionSystem();
	///Destructor
	~PositionSystem();
	///Deleted copy constructor and assign operator
	PositionSystem(const PositionSystem&) = delete;
	void operator=(const PositionSystem&) = delete;

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


	/*-----------------EDITOR METHODS--------------------*/

	///Creates component to entity and add it to container and json object
	SEuint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj) override final;

	///Removes component from entity and container and json object
	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj) override final;

	///Modifies component from entity
	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj) override final;

	///Returns plain Component* used in editor function.
	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

	static std::vector<CPosition> PositionComponents;

private:
	std::queue<SEint> m_free_cPos_indices;
};

}//namespace priv
}//namespace se


#endif