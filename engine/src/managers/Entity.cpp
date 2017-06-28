#include <managers/Entity.h>
#include <core/Engine.h>
#include <managers/EntityComponentManager.h>

namespace se
{
//Entity id count starts from 1;
SEuint Entity::entity_id_count = 1u;

Entity::Entity(std::string name)
	: name(name)
	, id(entity_id_count++)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}

Entity::Entity(std::string filepath, std::string entityName)
	: name(entityName)
	, id(entity_id_count++)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}

Entity::Entity(const Entity& other)
	: name(other.name)
	, id(entity_id_count++)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}
}//namespace se