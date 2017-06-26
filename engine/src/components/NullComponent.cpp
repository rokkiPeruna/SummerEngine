#include <components/NullComponent.h>
#include <managers/Entity.h>

namespace se
{
namespace priv
{
NullComponent::NullComponent(const Entity& entity, const char* name)
	: Component(COMPONENT_TYPE::NULL_COMPONENT)
{
	//TODO: Add message to log that informs that NullComponent was created.
	
	std::cout << entity.name << "  " << name << std::endl;
}
}
}