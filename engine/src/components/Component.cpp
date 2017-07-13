#include <components/Component.h>

namespace se
{
Component::Component(COMPONENT_TYPE type)
	: type(type)
	, id(0)
	, ownerID(0)
{

}

Component::~Component()
{

}

Component::Component(const Component& other)
	: type(other.type)
	, id(other.id)
	, ownerID(other.id)
{

}
}//namespace se