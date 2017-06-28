#include <components/NullComponent.h>
#include <managers/Entity.h>

namespace se
{
namespace priv
{
NullComponent::NullComponent(const Entity& entity, const char* name)
	: Component(nullComponent_id)
{
	//TODO: Add message to log that informs that NullComponent was created.
	
	std::cout << entity.name << "  " << name << std::endl;
}
}
}