#include <gui/CTransformableEditor.h>
#include <components/CTransformable.h>
#include <systems/TransformSystem.h>
#include <utility/EditorFunctions.h>


namespace se
{
namespace gui
{
CTransformableEditor::CTransformableEditor(priv::Engine& engine_ref)
	: CompEditorGui(engine_ref)
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	GraphicalUserInterface::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::TRANSFORMABLE, this);

	///Event handler
	m_engine.GetEventManager().RegisterEventHandler(m_event_handler);
}

void CTransformableEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::TRANSFORMABLE)
	{

		//SE_TODO: Check somehow that index is valid component!
		auto& comp = priv::TransformSystem::TransformableComponents.at(index_in_container);

		Keyboard keyboard;
		Mouse mouse;

		SEint mouse_pos_X = 0;
		SEint mouse_pos_Y = 0;

		if (keyboard.GetState(KeyboardState::W) && mouse.GetState(MouseState::Left_Button, &mouse_pos_X, &mouse_pos_Y))
		{
			Vec2f norm_mouse_pos = util::ScreenCoordsToNormOpenGLCoords(mouse_pos_X, mouse_pos_Y, Vec2f(gui::window_data::width, gui::window_data::heigth), m_engine.GetCamera()->GetPosition());
			comp.position.x = norm_mouse_pos.x;
			comp.position.y = norm_mouse_pos.y;
		}
		if (keyboard.GetState(KeyboardState::R))
		{
			comp.rotation += 10.f;
		}


		ImGui::DragFloat("Position X", &comp.position.x, 0.005f);
		ImGui::DragFloat("Position Y", &comp.position.y, 0.005f);
		ImGui::DragFloat("Position Z", &comp.position.z, 0.005f);
		
		ImGui::DragFloat("Rotation", &comp.rotation, 1.f);
		ImGui::DragFloat("Scale X", &comp.scale.x, 0.05f);
		ImGui::DragFloat("Scale Y", &comp.scale.y, 0.05f);

		comp.modelMatrix = glm::translate(Mat4f(1.0f), comp.position) * glm::rotate(Mat4f(1.0f), glm::radians(comp.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), comp.scale);

		component_obj.value().at("pos_x") = comp.position.x;
		component_obj.value().at("pos_y") = comp.position.y;
		component_obj.value().at("pos_z") = comp.position.z;
		component_obj.value().at("orig_x") = comp.origin.x;
		component_obj.value().at("orig_y") = comp.origin.y;
		component_obj.value().at("orig_z") = comp.origin.z;
		component_obj.value().at("rot") = comp.rotation;
		component_obj.value().at("scal_x") = comp.scale.x;
		component_obj.value().at("scal_y") = comp.scale.y;
		component_obj.value().at("scal_z") = comp.scale.z;
	}


}

}//namespace gui
}//namespace se