#include <systems/MovementSystem.h>
#include <core/Engine.h>
#include <imgui/imgui.h>

namespace se
{
CPosition* GetCPosition(SEuint owner_id)
{
	return priv::Engine::Instance().GetMovementSystem()->m_cpositions_map.at(owner_id);
}

CVelocity* GetCVelocity(SEuint owner_id)
{
	return priv::Engine::Instance().GetMovementSystem()->m_cvelocities_map.at(owner_id);
}

CPosition* AddCPosition(SEuint owner_id, CPosition component)
{
	component.ownerID = owner_id;
	component.type = CPosition_id;
	return priv::Engine::Instance().GetMovementSystem()->_createCPositionComponent(component);
}

CVelocity* AddCVelocity(SEuint owner_id, CVelocity component)
{
	component.ownerID = owner_id;
	component.type = CVelocity_id;
	return priv::Engine::Instance().GetMovementSystem()->_createCVelocityComponent(component);
}

//Update ImGui
namespace gui
{
void UpdateMovementSystemGUI()
{
	
}
}

}//namespace se