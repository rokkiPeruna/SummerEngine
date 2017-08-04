#ifndef SE_COLLISION_SYSTEM_H
#define SE_COLLISION_SYSTEM_H

//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CCollidable.h>

namespace se
{
///Getter method for CMovables components
CCollidable* GetCollidableComponent(SEint index);

namespace priv
{
///Brief: SE_TODO: Add description
class CollisionSystem : public ComponentSystem
{
	//Friend getter method for CMovables components
	friend CCollidable* se::GetCollidableComponent(SEint index);

public:
	///Default constructor.
	///1.param: const ptr to Engine -class
	CollisionSystem(Engine* engine_ptr);
	///Destructor
	~CollisionSystem();
	///Deleted copy constructor and assign operator
	CollisionSystem(const CollisionSystem&) = delete;
	void operator=(const CollisionSystem&) = delete;

	void Initialize() override final;

	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void ClearComponentContainers() override final;

	void OnEntityAdded(Entity& e, Dataformat_itr& entity_obj) override final;

	void OnEntityRemoved(Entity& e) override final;

	SEint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

private:
	std::vector<CCollidable> m_cCollidables;
	std::queue<SEint> m_free_cCollidables_indices;

	SEbool _checkAABBcoll(const Vec4f& a, const Vec4f& b);
};

}//Namespace priv
}//Namespace se

#endif