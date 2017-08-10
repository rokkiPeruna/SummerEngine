#include <systems/ComponentSystem.h>

namespace se
{
namespace priv
{
Engine* ComponentSystem::m_engine_ptr = nullptr;

ComponentSystem::ComponentSystem(Engine& engine_ref)
	: m_engine(engine_ref)
{
	if (!ComponentSystem::m_engine_ptr)
		m_engine_ptr = &m_engine;
}
}//namespace priv
}//namespace se