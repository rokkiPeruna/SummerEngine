#include <gui/EngineGui.h>

namespace se
{
namespace gui
{
EngineGui::EngineGui(priv::Engine& engine_ref, SEuint update_priority)
	: m_engine(engine_ref)
	, m_update_priority(update_priority)
{

}

EngineGui::~EngineGui()
{

}

void EngineGui::_setCamPosToEntity(SEuint entity_id, SEfloat z_pos)
{
	auto& epos = priv::TransformSystem::TransformableComponents.at(entity_id).position;
	m_engine.GetCamera()->SetPosition(Vec3f(epos.x, epos.y, z_pos));
}

}//namespace gui
}//namespace se