#include <systems/MovementSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>

namespace se
{
namespace priv
{

MovementSystem::MovementSystem()
	: m_cMovables{}
	, m_free_cMovables_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems! Must be done in every new system
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::MOVABLE, this);

}

MovementSystem::~MovementSystem()
{

}

void MovementSystem::Initialize()
{

}

void MovementSystem::Uninitialize()
{

}

void MovementSystem::Update(SEfloat deltaTime)
{
	for (auto& movable_comp : m_cMovables)
	{
		movable_comp.velocity += movable_comp.acceleration * deltaTime;
		movable_comp.position += movable_comp.velocity * deltaTime;
	}

}

void MovementSystem::ClearComponentContainers()
{
	m_cMovables.clear();
	m_free_cMovables_indices = {};
}

void MovementSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::MOVABLE))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::MOVABLE, entity_obj, m_cMovables, m_free_cMovables_indices);
	}
}

void MovementSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::MOVABLE))
	{
		m_free_cMovables_indices.push(e.components.at(COMPONENT_TYPE::MOVABLE));
	}
}

SEuint MovementSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::MOVABLE)
	{
		return _createComponent_helper<CMovable>(entity, component_type, entity_obj, m_cMovables, m_free_cMovables_indices);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void MovementSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::MOVABLE)
	{
		m_free_cMovables_indices.push(_removeComponent_helper(entity, component_type, entity_obj));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}


}//namespace priv
}//namespace se