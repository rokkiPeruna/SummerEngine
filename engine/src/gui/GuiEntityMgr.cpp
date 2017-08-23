#include <gui/GuiEntityMgr.h>
#include <gui/GuiCompMgr.h>
#include <typeindex>


namespace se
{
namespace gui
{
GuiEntityMgr::GuiEntityMgr(priv::Engine& engine_ref, GuiCompMgr* gui_comp_mgr_ptr, SEuint update_priority)
	: ManagerGui(engine_ref, update_priority)
	, m_entity_mgr(nullptr)
	, m_comp_mgr(nullptr)
	, m_gui_comp_mgr(gui_comp_mgr_ptr)
	, m_gui_scene_name("NO ACTIVE SCENE")
{
	m_entity_mgr = &m_engine.GetEntityMgr();
	m_comp_mgr = &m_engine.GetCompMgr();
	assert(m_entity_mgr && m_comp_mgr && m_gui_comp_mgr);

}

void GuiEntityMgr::Update()
{
	assert(m_entity_mgr);
	assert(m_comp_mgr);

	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(window_data::width / 2.0f, window_data::heigth / 2.0f), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Entity editor", &elem_visibility::show_entity_comp_mgr_window); ImGui::SameLine();
	ImGui::Text(m_gui_scene_name.c_str());
	ImGui::Separator();

	if (!m_entity_mgr->GetCurrentScene())
	{
		ImGui::End();
		m_gui_scene_name = "NO ACTIVE SCENE";
		return;
	}
	else
		m_gui_scene_name = m_entity_mgr->GetCurrentScene()->GetName();

	if (ImGui::CollapsingHeader("Create entity"))
	{
		ImGui::Separator();
		static SEchar entityname[32];
		ImGui::InputText("Name", entityname, 32, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(entityname) != 0)
		{
			if (ImGui::Button("Create!"))
			{
				m_event_handler.SendEvent(SE_Event_CreateBasicEntity(entityname));	
				m_gui_comp_mgr->InvalidateComponentObj();
				memset(&entityname[0], 0, sizeof(entityname));
			}
		}
	}
	else if (ImGui::CollapsingHeader("Save as entity template"))
	{
		ImGui::Separator();
		for (auto& e : m_entity_mgr->GetEntityNameToID())
		{
			//ImGui::Bullet();
			if (ImGui::SmallButton(e.first.c_str()))
			{
				m_event_handler.SendEvent(SE_Cmd_SaveEntityAsTemplate(&m_entity_mgr->GetEntities().at(e.second)));
			}
		}
	}
	else if (ImGui::CollapsingHeader("Entities"))
	{
		ImGui::Separator();
		for (auto& e : m_entity_mgr->GetEntityNameToID())
		{
			//ImGui::Bullet();
			if (ImGui::SmallButton(e.first.c_str()))
			{
				//Inform GuiCompMgr that json object pointing to current component has been invalidated
				m_gui_comp_mgr->InvalidateComponentObj();
				elem_visibility::show_component_mgr_window = true;

				m_event_handler.SendEvent(SE_Cmd_SetEntityAsCurrent(&m_entity_mgr->GetEntities().at(e.second)));
			}
		}
	}
	else if (ImGui::CollapsingHeader("Delete entity"))
	{
		ImGui::Separator();
		for (auto& e : m_entity_mgr->GetEntityNameToID())
		{
			if (ImGui::Button(e.first.c_str()))
			{
				char ename[32];
				memcpy(ename, e.first.c_str(), sizeof(ename));
				m_event_handler.SendEvent(SE_Cmd_DeleteEntityByName(ename));
				break;
			}
		}
	}
	ImGui::End();
}

}//namespace gui
}//namespace se