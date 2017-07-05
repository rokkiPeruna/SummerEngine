#include <managers/Entity.h>
#include <core/Engine.h>
#include <managers/EntityComponentManager.h>

namespace se
{
Entity::Entity(std::string name)
	: name(name)
	, id(0)
	, sceneId(0)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}

Entity::Entity(const Entity& other)
	: name(other.name)
	, id(0)
	, sceneId(0)
	, componentMask(0)
	, childrenIDs{}
	, numOfChildren(0)
{

}
}//namespace se