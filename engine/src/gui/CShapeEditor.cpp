#include <gui/CShapeEditor.h>
#include <systems/TransformSystem.h>
#include <core/Render.h>

namespace se
{
namespace gui
{
CShapeEditor::CShapeEditor(priv::Engine& engine_ref)
	: CompEditorGui(engine_ref)
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	priv::Engine::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::SHAPE, this);
}

void CShapeEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::SHAPE)
	{
		//Store the id of the transform this shape had so we can later assing it back to a newly formed shape.
		//Also store owner id
		SEint id = GetShapeComponent(index_in_container)->my_Transform;
		SEint owner_id = GetShapeComponent(index_in_container)->ownerID;
		CShape& comp = *GetShapeComponent(index_in_container);
		
		Entity* tmpEntity = m_engine.GetEntityMgr().GetCurrentEntity();
		priv::Render* tmpRender = m_engine.GetCurrentRenderer();
		
		if (ImGui::Button("Triangle"))
		{
			tmpRender->OnRendableComponentChanged(*tmpEntity);
			comp = CShape(3);
			comp.my_Transform = id;
			comp.ownerID = owner_id;
			tmpRender->OnEntityAdded(*tmpEntity);
		}
		if (ImGui::Button("Rectangle"))
		{
			tmpRender->OnRendableComponentChanged(*tmpEntity);
			comp = CShape(4);
			comp.my_Transform = id;
			comp.ownerID = owner_id;
			tmpRender->OnEntityAdded(*tmpEntity);
		}
		if (ImGui::Button("Circle"))
		{
			tmpRender->OnRendableComponentChanged(*tmpEntity);
			comp = CShape(30);
			comp.my_Transform = id;
			comp.ownerID = owner_id;
			tmpRender->OnEntityAdded(*tmpEntity);
		}
		if (ImGui::Button("Add indie"))
		{
			tmpRender->OnRendableComponentChanged(*tmpEntity);
			comp = CShape(static_cast<SEushort>(comp.points.size()) + 1);
			comp.my_Transform = id;
			comp.ownerID = owner_id;
			tmpRender->OnEntityAdded(*tmpEntity);
		}
		if (ImGui::Button("Remove indice") && comp.points.size() > 3)
		{
			tmpRender->OnRendableComponentChanged(*tmpEntity);
			comp = CShape(static_cast<SEushort>(comp.points.size()) - 1);
			comp.my_Transform = id;
			comp.ownerID = owner_id;
			tmpRender->OnEntityAdded(*tmpEntity);
		}

	}
}

}//namespace gui
}//namespace se