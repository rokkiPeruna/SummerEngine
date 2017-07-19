#ifndef SE_TRANSFORM_SYSTEM_H
#define SE_TRANSFORM_SYSTEM_H

//Include standard library

//Include external

//Include SE
#include <systems/ComponentSystem.h>
#include <components/CTransformable.h>



namespace se
{
namespace priv
{

///Brief : TransformSystem handels components rotation, scale and pivot related things.

class TransformSystem : public ComponentSystem
{

public:

	///Default constructor
	TransformSystem();
	///Destructor
	~TransformSystem();
	///Delete copy constructor and assingment operator
	TransformSystem(const TransformSystem&) = delete;
	void operator=(const TransformSystem&) = delete;

	///Initialize this system
	void Initialize() override final;
	///Uninitialize this system
	void Uninitialize() override final;

	///Run through logic using components as values 
	void Update(SEfloat deltaTime) override final;

	///Clear component containers
	void ClearComponentContainers() override final;

	///OnEntityAdded checks if entity has components that need to be builded to this system
	void OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj) override final;

	void OnEntityRemoved(Entity& e) override final;

	///Creates component to entity and add it to container and json object
	SEuint CreateComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&) override final;
	
	///Removes component from entity and container and json object
	void RemoveComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&) override final;

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj) override final {}

	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) { return nullptr; }

private:

	///Component containers(vectors) and free index containers(queues)
	std::vector<CTransformable> m_cTransformables;
	std::queue<SEint> m_free_cTransformables_indices;

};


} // !namespace priv

} // !namespace se


#endif