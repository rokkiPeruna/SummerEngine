#include <gui/CCollidableEditor.h>
#include <core/Engine.h>
#include <components/CCollidable.h>

namespace se
{
namespace gui
{
CCollidableEditor::CCollidableEditor()
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	priv::Engine::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::COLLIDABLE, this);
}

void CCollidableEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::COLLIDABLE)
	{
		auto comp = GetCollidableComponent(index_in_container);

		ImGui::SliderFloat("aabb_min", &comp->aabb.x, -10.0f, 10.0f);
		ImGui::SliderFloat("aabb_max", &comp->aabb.y, -10.0f, 10.0f);

		component_obj.value().at("min") = comp->aabb.x;
		component_obj.value().at("max") = comp->aabb.y;
	}
}

}//namespace gui
}//namespace se