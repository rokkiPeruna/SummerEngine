#include <systems/ComponentSystem.h>

namespace se
{
namespace priv
{
ComponentSystem::ComponentSystem(std::shared_ptr<EntityComponentManager> ecm_ptr)
	: m_ecm_ptr(ecm_ptr)
{

}

ComponentSystem::~ComponentSystem()
{

}
}//namespace priv
}//namespace se