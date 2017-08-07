#include <gui/CDynamicEditor.h>
#include <components/CDynamic.h>
#include <systems/MovementSystem.h>

namespace se
{
namespace gui
{
CDynamicEditor::CDynamicEditor(priv::Engine& engine_ref)
	: CompEditorGui(engine_ref)
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	priv::Engine::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::DYNAMIC, this);
}

void CDynamicEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::DYNAMIC)
	{

		//SE_TODO: Check somehow that index is valid component!
		CDynamic* comp = GetDynamicComponent(index_in_container);
		ImGui::SliderFloat("velocity_x", &comp->velocity.x, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_y", &comp->velocity.y, 0.0f, 200.0f);
		ImGui::SliderFloat("velocity_z", &comp->velocity.z, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_x", &comp->acceleration.x, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_y", &comp->acceleration.y, 0.0f, 200.0f);
		ImGui::SliderFloat("acceleration_z", &comp->acceleration.z, 0.0f, 200.0f);

		component_obj.value().at("velo_x") = comp->velocity.x;
		component_obj.value().at("velo_y") = comp->velocity.y;
		component_obj.value().at("velo_z") = comp->velocity.z;
		component_obj.value().at("acc_x") = comp->acceleration.x;
		component_obj.value().at("acc_y") = comp->acceleration.y;
		component_obj.value().at("acc_z") = comp->acceleration.z;
	}

}

}//namespace gui
}//namespace se