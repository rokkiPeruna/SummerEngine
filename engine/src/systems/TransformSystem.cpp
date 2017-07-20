#include <systems/TransformSystem.h>
#include <core/Messages.h>
#include <imgui/imgui.h>
#include <ids/ComponentTypeList.h>

#include <core/Engine.h>


namespace se
{
namespace priv
{

TransformSystem::TransformSystem() 
	: m_cTransformables{}
	, m_free_cTransformables_indices{}
{
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TRANSFORMABLE, this);
}


TransformSystem::~TransformSystem()
{

}

void TransformSystem::Initialize()
{

}

void TransformSystem::Uninitialize()
{

}

void TransformSystem::Update(SEfloat deltaTime)
{
	for (auto& transformable_comp : m_cTransformables)
	{
		
	}
}

void TransformSystem::ClearComponentContainers()
{
	m_cTransformables.clear();
	m_free_cTransformables_indices = {};
}


void TransformSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::TRANSFORMABLE))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::TRANSFORMABLE, entity_obj, m_cTransformables, m_free_cTransformables_indices);
	}
}

void TransformSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::MOVABLE))
	{
		m_free_cTransformables_indices.push(e.components.at(COMPONENT_TYPE::TRANSFORMABLE));
	}
}

SEuint TransformSystem::CreateComponent(Entity& e, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		return _createComponent_helper<CTransformable>(e, COMPONENT_TYPE::TRANSFORMABLE, entity_obj, m_cTransformables, m_free_cTransformables_indices);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void TransformSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TRANSFORMABLE)
	{
		m_free_cTransformables_indices.push(_removeComponent_helper(entity, component_type, entity_obj));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}



}
}