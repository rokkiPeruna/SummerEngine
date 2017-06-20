#include <managers/Entity.h>

namespace se
{
Entity::Entity(std::string name)
	: name(name)
{

}

Entity::Entity(std::string filepath, std::string entityName)
	: name(entityName)
{

}

Entity::Entity(const Entity& other)
	:name(other.name)
{

}

void Entity::AddComponent()
{

}

void Entity::RemoveComponent()
{

}

void Entity::ReplaceComponent()
{

}

std::shared_ptr<priv::Component> Entity::GetComponent(/*COMPONENT_TYPE type*/)
{
	//Use COMPONENT_TYPE and entity's name to make a unigue identifier
}

}//namespace se