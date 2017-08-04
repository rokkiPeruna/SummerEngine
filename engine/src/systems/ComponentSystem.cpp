#include <systems/ComponentSystem.h>
#include <core/Engine.h>

namespace se
{
namespace priv
{
Engine* ComponentSystem::m_engine = nullptr;

ComponentSystem::ComponentSystem(Engine* engine_ptr)
{
	if (!ComponentSystem::m_engine)
		m_engine = engine_ptr;
}

ComponentSystem::~ComponentSystem()
{
	m_engine = nullptr;
}
}//namespace priv
}//namespace se