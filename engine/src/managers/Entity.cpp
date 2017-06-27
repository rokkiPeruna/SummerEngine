#include <managers/Entity.h>
#include <core/Engine.h>

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

std::shared_ptr<priv::Component> Entity::AddComponent(priv::Component* component)
{
	m_myComponents.emplace(
		componentDictionary.at(component->myType),
		sysForCompDictionary.at(component->myType)->InitializeNewComponent(*component)
	);//TÄMÄ KOSAHTAA!!
		//sysForCompDictionary.at(component.myType)->InitializeNewComponent(component) nullptr!!!!

		//Vaihda static SystemForComponentDictionary siten, että COMPONENT_TYPEn parina on funktiopointteri systeemin InitializeNewComponent metodiin
		//Tämä mahdollistaa sen, että systeemi voi initialisoida useampia eri komponenttityyppejä joustavammin
}

void Entity::RemoveComponent()
{

}

void Entity::ReplaceComponent()
{

}

//std::shared_ptr<priv::Component> Entity::GetComponent(COMPONENT_TYPE type)
//{
//	//Use COMPONENT_TYPE to find correct component
//	auto itr = m_myComponents.find(type);
//	//If found, return pointer
//	if (itr != m_myComponents.end())
//		return itr->second;
//	//If not, send message and return nullptr
//	else
//	{
//		//TODO: Send message to log
//		return nullptr;
//	}
//}

const SEuint Entity::GetNumOfChildren() const
{
	return m_numOfChildren;
}

SEuint Entity::AddNumOfChildren()
{
	return ++m_numOfChildren;
}

}//namespace se