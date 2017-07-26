#include <systems/CollisionSystem.h>
#include <core/Engine.h>
#include <imgui/imgui.h>


namespace se
{
CCollidable* GetCollidableComponent(SEint index)
{
	return &priv::Engine::Instance().GetCollisionSystem()->m_cCollidables.at(index);
}

namespace priv
{
CollisionSystem::CollisionSystem()
	: m_cCollidables{}
	, m_free_cCollidables_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::COLLIDABLE, this);
}

CollisionSystem::~CollisionSystem()
{

}

void CollisionSystem::Initialize()
{

}

void CollisionSystem::Uninitialize()
{

}

void CollisionSystem::Update(SEfloat deltaTime)
{
	//Doesn't modify transform components, should be thread safe?
	if (m_cCollidables.empty())
		return;

	auto& transforms = TransformSystem::TransformableComponents;
	for (auto& itr = m_cCollidables.begin(); itr != (m_cCollidables.end() - 1); ++itr)
	{
		//Translate bounding box to world coordinates
		auto f_world_aabb = (*itr).aabb + Vec2f(transforms.at((*itr).ownerID).position);
		for (auto& next = itr + 1; next != m_cCollidables.end(); ++next)
		{
			//Check for broad phase collision (AABB)
			auto s_world_aabb = (*next).aabb + Vec2f(transforms.at((*next).ownerID).position);

			if (
				f_world_aabb.y > s_world_aabb.x &&
				f_world_aabb.x < s_world_aabb.y &&
				f_world_aabb.y > s_world_aabb.x &&
				f_world_aabb.x < s_world_aabb.y
				||
				s_world_aabb.y > f_world_aabb.x &&
				s_world_aabb.x < f_world_aabb.y &&
				s_world_aabb.y > f_world_aabb.x &&
				s_world_aabb.x < f_world_aabb.y
				)
			{
				//If true, check for narrow phase collision
				std::cout << "Colliding!" << std::endl;
			}
		}
	}
}

void CollisionSystem::ClearComponentContainers()
{
	m_cCollidables.clear();
	m_free_cCollidables_indices = {};
}

void CollisionSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::COLLIDABLE))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::COLLIDABLE, entity_obj, m_cCollidables, m_free_cCollidables_indices);
	}
}

void CollisionSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::COLLIDABLE))
	{
		m_free_cCollidables_indices.push(e.components.at(COMPONENT_TYPE::COLLIDABLE));
	}
}

/*-----------------EDITOR METHODS--------------------*/

SEint CollisionSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::COLLIDABLE)
	{
		SEint testi = _createComponent_helper(entity, component_type, entity_obj, m_cCollidables, m_free_cCollidables_indices);
		auto bugi = m_cCollidables.at(testi).ownerID;
		return testi;
	}
	else
	{
		MessageWarning(CollisionSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void CollisionSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
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

}//namespace priv
}//namespace se