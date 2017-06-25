#include <managers/Entity.h>
#include <systems/ComponentSystem.h>

//Components
#include <components/CTransform2D.h>

namespace se
{
Entity::Entity(std::string name)
	: name(name)
	, m_numOfChildren(0)
	, m_myComponents{}
{

}

Entity::Entity(std::string filepath, std::string entityName)
	: name(entityName)
	, m_numOfChildren(0)
	, m_myComponents{}
{

}

Entity::Entity(const Entity& other)
	:name(other.name)
	, m_numOfChildren(0)
	, m_myComponents{}
{
	//TODO: Copy components
}

void Entity::AddComponent(std::shared_ptr<priv::Component> component)
{
	auto c = component->mySystem->CreateNewComponent(component);
	//m_myComponents.emplace(c->myType, c);
}


void Entity::RemoveComponent()
{

}

void Entity::ReplaceComponent()
{

}

std::shared_ptr<priv::Component> Entity::GetComponent(COMPONENT_TYPE type)
{
	//Use COMPONENT_TYPE to find correct component
	auto itr = m_myComponents.find(type);
	//If found, return pointer
	if (itr != m_myComponents.end())
		return itr->second;
	//If not, send message and return nullptr
	else
	{
		//TODO: Send message to log
		return nullptr;
	}
}

const SEuint Entity::GetNumOfChildren() const
{
	return m_numOfChildren;
}

SEuint Entity::AddNumOfChildren()
{
	return ++m_numOfChildren;
}

}//namespace se