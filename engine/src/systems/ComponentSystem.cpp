#include <systems/ComponentSystem.h>

namespace se
{
namespace priv
{
ComponentSystem::ComponentSystem(Engine& engine_ref)
	: m_engine{ engine_ref }
	, m_event_handler{}
{

}

}//namespace priv
}//namespace se