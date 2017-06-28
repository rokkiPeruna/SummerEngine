#include <systems/MovementSystem.h>


namespace se
{
namespace priv
{
MovementSystem::MovementSystem()
{

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

CPosition* MovementSystem::_createCPositionComponent(CPosition& component)
{
	if (m_cpositions_map.count(component.ownerID) == 0)
	{
		m_cpositions.emplace_back(component);
		m_cpositions_map.emplace(component.ownerID, &m_cpositions.back());
		return &m_cpositions.back();
	}
	//TODO: Send message to log
	return nullptr;
}
CVelocity* MovementSystem::_createCVelocityComponent(CVelocity& component)
{
	if (m_cvelocities_map.count(component.ownerID) == 0)
	{
		m_cvelocities.emplace_back(component);
		m_cvelocities_map.emplace(component.ownerID, &m_cvelocities.back());
		return &m_cvelocities.back();
	}
	//TODO: Send message to log
	return nullptr;
}


}//namespace priv
}//namespace se