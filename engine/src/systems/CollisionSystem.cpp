#include <systems/CollisionSystem.h>
#include <systems/TransformSystem.h>
#include <managers/EntityManager.h>

namespace se
{
CCollidable* GetCollidableComponent(SEint index)
{

	return &priv::Engine::Ptr->GetCollisionSystem().m_cCollidables.at(index);
}

namespace priv
{
CollisionSystem::CollisionSystem(Engine& engine_ref)
	: ComponentSystem(engine_ref)
	, m_cCollidables{}
	, m_free_cCollidables_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::COLLIDABLE, this);
}

void CollisionSystem::Initialize()
{

}

void CollisionSystem::Uninitialize()
{

}

void CollisionSystem::CheckEvents()
{

}

void CollisionSystem::Update(SEfloat)
{
	if (m_cCollidables.empty())
		return;

	//Check messages!!-


	//auto* entities = &m_engine.GetEntityMgr().GetEntities();
	
	for (auto& itr = m_cCollidables.begin(); itr != (m_cCollidables.end() - 1); ++itr)
	{
		//Check if ownerless
		if ((*itr).ownerID < 0)
			continue;

		//Translate bounding box to world coordinates
		//auto f_world_aabb = (*itr).aabb + Vec2f(transforms.at((*itr).ownerID).position);
		auto f = Vec4f((*itr).aabb, 0.0f, 0.0f) * (*itr).modelMat;
		for (auto& next = itr + 1; next != m_cCollidables.end(); ++next)
		{
			//Check for broad phase collision (AABB)
			//auto s_world_aabb = (*next).aabb + Vec2f(transforms.at((*next).ownerID).position);
			auto s = Vec4f((*next).aabb, 0.0f, 0.0f) * (*next).modelMat;

			if (_checkAABBcoll(f, s))
			{

			}


		}
	}
}

void CollisionSystem::ClearComponentContainers()
{
	m_cCollidables.clear();
	m_free_cCollidables_indices = {};
}

void CollisionSystem::OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj)
{
	if (entity.components.count(COMPONENT_TYPE::COLLIDABLE))
	{
		SEint index = _onEntityAdded_helper(entity, COMPONENT_TYPE::COLLIDABLE, entity_obj, m_cCollidables, m_free_cCollidables_indices);
		///Initialize CCollidable's run-time-only value
		m_cCollidables.at(index).modelMat = TransformSystem::TransformableComponents.at(entity.id).modelMatrix;
	}
}

void CollisionSystem::OnEntityRemoved(Entity& entity)
{
	if (entity.components.count(COMPONENT_TYPE::COLLIDABLE))
	{
		m_free_cCollidables_indices.push(entity.components.at(COMPONENT_TYPE::COLLIDABLE));
	}
}

/*-----------------EDITOR METHODS--------------------*/

SEint CollisionSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::COLLIDABLE)
	{
		SEint index = _createComponent_helper(entity, component_type, entity_obj, m_cCollidables, m_free_cCollidables_indices);
		///Initialize CCollidable's run-time-only value
		m_cCollidables.at(index).modelMat = TransformSystem::TransformableComponents.at(entity.id).modelMatrix;
		return index;
	}
	else
	{
		MessageWarning(CollisionSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void CollisionSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::COLLIDABLE)
	{
		m_free_cCollidables_indices.push(_removeComponent_helper(entity, component_type, entity_obj, m_cCollidables));
	}
	else
	{
		MessageWarning(CollisionSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

Component* CollisionSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::COLLIDABLE)
	{
		return &m_cCollidables.at(index_in_container);
	}
	else
		return nullptr;
}


SEbool CollisionSystem::_checkAABBcoll(const Vec4f& a, const Vec4f& b)
{
	return
		a.y > b.x &&
		a.x < b.y &&
		a.y > b.x &&
		a.x < b.y
		||
		b.y > a.x &&
		b.x < a.y &&
		b.y > a.x &&
		b.x < a.y;
}

}//namespace priv
}//namespace se