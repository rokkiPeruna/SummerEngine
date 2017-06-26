#ifndef SE_NULLCOMPONENT_H
#define SE_NULLCOMPONENT_H

///STL includes:
#include <typeindex>

///SE includes:
#include <components/Component.h>

namespace se
{
class Entity;
namespace priv
{

///Brief: NullComponent is a helper class that gets created if entity's component
///is queried with component that it doesn't have. NullComponent's constructor
///sends message to log to inform that query has failed.
class NullComponent : public Component
{
public:
	///Default constructor that sends message to log informing
	///user that query for entity's component has failed.
	NullComponent(const Entity& entity, const char* name);

};
}//namespace priv
}//namespace se
#endif
