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
	: m_cpositions{}
	, m_free_cposition_indices{}
	, m_cvelocities{}
	, m_free_cvelocity_indices{}
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems! Must be done in every new system
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::POSITION, this);
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::VELOCITY, this);

	//Reserve space for vectors, SE_TODO: The amount to be reserved should come from user!!
	m_cpositions.reserve(20);
	m_cvelocities.reserve(20);

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

void MovementSystem::Update(float deltaTime)
{
	if (SDLK_p)
	{

		for (auto& c : m_cpositions)
		{
			std::cout << c.x << " " << c.y << " " << c.z << std::endl;
		}
	}



}

void MovementSystem::ClearComponentContainers()
{
	m_cpositions.clear();
	m_cvelocities.clear();
}

void MovementSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::POSITION))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::POSITION, entity_obj, m_cpositions, m_free_cposition_indices);
	}
	if (e.components.count(COMPONENT_TYPE::VELOCITY))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::VELOCITY, entity_obj, m_cvelocities, m_free_cvelocity_indices);
	}
}

void MovementSystem::OnEntityRemoved(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::POSITION))
	{

	}
	if (e.components.count(COMPONENT_TYPE::VELOCITY))
	{

	}
}

SEuint MovementSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	SEint index = -1;
	//Since movement system is responsible for multiple different components, check which this is:
	if (component_type == COMPONENT_TYPE::POSITION)
	{
		return _createComponent_helper<CPosition>(entity, component_type, entity_obj, m_cpositions, m_free_cposition_indices);
	}
	else if (component_type == COMPONENT_TYPE::VELOCITY)
	{
		return _createComponent_helper<CVelocity>(entity, component_type, entity_obj, m_cvelocities, m_free_cvelocity_indices);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void MovementSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	//Since movement system is responsible for multiple different components, check which this is:
	if (component_type == COMPONENT_TYPE::POSITION)
	{
		m_free_cposition_indices.push(_removeComponent_helper(entity, component_type, entity_obj));
	}
	else if (component_type == COMPONENT_TYPE::VELOCITY)
	{
		m_free_cvelocity_indices.push(_removeComponent_helper(entity, component_type, entity_obj));
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}


}//namespace priv
}//namespace se