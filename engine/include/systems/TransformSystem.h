#ifndef SUMMER_ENGINE_TRANSFORM_SYSTEM_H
#define SUMMER_ENGINE_TRANSFORM_SYSTEM_H

//STL includes:
#include <set>


///SE includes:
#include <systems/ComponentSystem.h>
#include <components/CTransformable.h>
#include <components/CShape.h>


namespace se
{
///Getter for CShape components
CShape* GetShapeComponent(SEint index);
CTransformable* GetTransformComponent(SEint index);

namespace priv
{
///Brief: TransformSystem handles CTransformables components. Since transform components are used through out different systems,
///TransformSystem reveals it's component container to public access as static container. 
///Because entities are tightly coupled with CTransformables components (every entity has one), CTransformables components
///are arranged in a way that ensures that CTransformables component's index in container is the same as it's owner's id.
///This enables easy search for entity's transform: TransformableComponents.at(myComponent.ownerID) returns a reference to correct CTransformable component.
///Downside for this is that CTransformable container is partly handled in EntityManager. EntityManager reserves enough space for container
///to fit all scene's entities' CTransformables plus some extra. See EntityManager.cpp InitWithNewScene for details.
class TransformSystem : public ComponentSystem
{
	friend class RenderSystem;
	//Friend getter method for CMovables components
	friend CShape* se::GetShapeComponent(SEint index);
	friend CTransformable* se::GetTransformComponent(SEint index);

public:

	///Default constructor.
	///1.param: reference to Engine -class
	TransformSystem(Engine& engine_ref);
	//
	~TransformSystem() = default;
	TransformSystem(const TransformSystem&) = delete;
	void operator=(const TransformSystem&) = delete;
	TransformSystem(TransformSystem&&) = delete;
	void operator=(TransformSystem&&) = delete;

	///Initialize this system
	void Initialize() override final;
	///Uninitialize this system
	void Uninitialize() override final;

	///Run through logic using components as values 
	void Update(SEfloat deltaTime) override final;

	void CheckEvents() override final;

	///Clear component containers
	void ClearComponentContainers() override final;

	///OnEntityAdded checks if entity has components that need to be builded to this system
	void OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj) override final;

	void OnEntityRemoved(Entity& entity) override final;

	///Creates component to entity and add it to container and jsonobject
	SEint CreateComponent(Entity& entity, COMPONENT_TYPE, Dataformat_itr& entity_obj) override final;

	///Removes component from entity and container and json object
	void RemoveComponent(Entity& entity, COMPONENT_TYPE, Dataformat_itr& entity_obj) override final;

	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

	///Every entity has CTransformable component and they are frequently needed in other system, so TransformSystem reveals the static container as public
	static std::vector<CTransformable> TransformableComponents;

	const std::vector<CShape>& GetCShapesContainer() { return m_cShapes; }


private:
	std::vector<CShape> m_cShapes;
	std::queue<SEint> m_free_cShape_indices;

	std::set<SEint> m_recalc_transf_indices;
};

} // !namespace priv
} // !namespace se

#endif