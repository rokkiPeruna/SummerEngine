#include <systems/ComponentSystem.h>
#include <core/Engine.h>

namespace se
{
namespace priv
{
std::shared_ptr<Engine> ComponentSystem::m_engine = nullptr;

ComponentSystem::ComponentSystem(std::shared_ptr<Engine> engine_ptr)
{
	if (!ComponentSystem::m_engine)
		m_engine = engine_ptr;
}

ComponentSystem::~ComponentSystem()
{

}
}//namespace priv
}//namespace se