#include <components/Component.h>

namespace se
{
namespace priv
{
Component::Component(COMPONENT_TYPE type)
	: myType(type)
	, overwritable(false)
	, mySystem(nullptr)
{

}

Component::~Component()
{

}

Component::Component(const Component& other)
	: myType(other.myType)
	, overwritable(false)
	, mySystem(other.mySystem)
{

}
}//namespace priv
}//namespace se