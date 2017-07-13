#include <managers/Entity.h>
#include <core/Engine.h>
#include <managers/EntityManager.h>

namespace se
{
Entity::Entity(std::string name, SEuint id)
	: name(name)
	, id(id)
	, components{}
{

}

Entity::Entity(const Entity& other)
	: name(other.name)
	, id(other.id)
	, components(other.components)
{

}
}//namespace se