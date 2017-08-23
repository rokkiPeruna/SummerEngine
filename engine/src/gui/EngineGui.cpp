#include <gui/EngineGui.h>

namespace se
{
namespace gui
{
EngineGui::EngineGui(priv::Engine& engine_ref, SEuint update_priority)
	: m_engine(engine_ref)
	, m_event_handler{}
	, m_update_priority(update_priority)
{

}

Vec3f EngineGui::_getEntityPos(SEuint entity_id)
{
	return priv::TransformSystem::TransformableComponents.at(entity_id).position;

}

}//namespace gui
}//namespace se