#include <managers/Entity.h>
#include <core/Engine.h>
#include <managers/EntityManager.h>

namespace se
{
Entity::Entity(std::string name, SEuint id)
	: name(name)
	, id(id)
	, sceneId(0)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}

Entity::Entity(const Entity& other)
	: name(other.name)
	, id(other.id)
	, sceneId(0)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}
}//namespace se