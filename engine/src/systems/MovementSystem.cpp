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

}

SEuint MovementSystem::AddComponent(Entity& entity, COMPONENT_TYPE component_type)
{
	//Check that entity doesn't already have component
	if (entity.components.count(component_type) != 0)
	{
		DebugMessageInfo(MovementSys_id) << "Entity [" + entity.name + "] already has that component!";
		return 0;
	}

	SEuint index = 0;
	//Since movement system is responsible for multiple different components, check which this is:
	if (component_type == COMPONENT_TYPE::POSITION)
	{
		//Emplace new CPosition component
		m_cpositions.emplace_back(CPosition());
		//Calculate it's index in vector
		index = (m_cpositions.end() - 1) - m_cpositions.begin();
		//Add component type and it's index in container to entity 
		entity.components.emplace(component_type, index);
		DebugMessage(MovementSys_id) << "Added PositionComponent!";
		return index;
	}
	else if (component_type == COMPONENT_TYPE::VELOCITY)
	{
		//Emplace new CPosition component
		m_cvelocities.emplace_back(CVelocity());
		//Calculate it's index in vector
		index = (m_cvelocities.end() - 1) - m_cvelocities.begin();
		//Add component type and it's index in container to entity 
		entity.components.emplace(component_type, index);
		DebugMessage(MovementSys_id) << "Added VelocityComponent!";
		return index;
	}
	else
	{
		MessageWarning(MovementSys_id) << "Somehow tried to add component that doesn't belong to this system!!";
		return 0;
	}
}

}//namespace priv
}//namespace se