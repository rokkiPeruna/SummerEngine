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
	if ( SDLK_p)
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
		_onEntityAdded_helper(e, COMPONENT_TYPE::POSITION, entity_obj, m_cpositions);
	}
	if (e.components.count(COMPONENT_TYPE::VELOCITY))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::VELOCITY, entity_obj, m_cvelocities);
	}
}

void MovementSystem::OnEntityRemoved(Entity& e, SceneFileFormatIterator& entity_obj)
{
	//SE_TODO: Logic!
}

SEuint MovementSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& itr)
{
	SEuint index = 0;
	//Since movement system is responsible for multiple different components, check which this is:
	if (component_type == COMPONENT_TYPE::POSITION)
	{
		return _createComponent_helper<CPosition>(entity, component_type, itr, m_cpositions);
	}
	else if (component_type == COMPONENT_TYPE::VELOCITY)
	{
		return _createComponent_helper<CVelocity>(entity, component_type, itr, m_cvelocities);
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

}//namespace priv
}//namespace se