#include <gui/EngineGui.h>

namespace se
{
namespace gui
{
EngineGui::EngineGui(priv::Engine& engine_ref, SEuint update_priority)
	: m_engine(engine_ref)
	, m_event_handler(nullptr)
	, m_update_priority(update_priority)
{
	priv::Engine::Ptr->GetEventManager().RegisterEventHandler(m_event_handler);
}

Vec3f EngineGui::_getEntityPos(SEuint entity_id)
{
	return priv::TransformSystem::TransformableComponents.at(entity_id).position;

}

}//namespace gui
}//namespace se