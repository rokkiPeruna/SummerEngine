#include <gui/GuiEntityMgr.h>
#include <gui/GuiCompMgr.h>
#include <typeindex>
#include <systems/TransformSystem.h> //For setting camera position when new entity is created or entity is choosed

namespace se
{
namespace gui
{
GuiEntityMgr::GuiEntityMgr(priv::Engine& engine_ref, GuiCompMgr* gui_comp_mgr_ptr)
	: ManagerGui(engine_ref)
	, m_entity_mgr(nullptr)
	, m_comp_mgr(nullptr)
	, m_gui_comp_mgr(gui_comp_mgr_ptr)
	, m_gui_scene_name("NO ACTIVE SCENE")
{
	m_entity_mgr = &m_engine.GetEntityMgr();
	m_comp_mgr = &m_engine.GetCompMgr();
	assert(m_entity_mgr && m_comp_mgr && m_gui_comp_mgr);
}

GuiEntityMgr::~GuiEntityMgr()
{

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
		static SEchar entityname[64];
		ImGui::InputText("Name", entityname, 64, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(entityname) != 0)
		{
			if (ImGui::Button("Create!"))
			{
				m_entity_mgr->CreateEntityOnEditor(entityname);

				SEint entityid = m_entity_mgr->GetEntityNameToID().at(entityname);
				m_entity_mgr->SetCurrentEntity(&m_entity_mgr->GetEntities().at(entityid));
				m_comp_mgr->SetCurrentEntity(&m_entity_mgr->GetEntities().at(entityid));
				m_comp_mgr->SetCurrentComponent(COMPONENT_TYPE::TRANSFORMABLE, entityid);
				//Inform GuiCompMgr that json object pointing to current component has been invalidated		
				m_gui_comp_mgr->InvalidateComponentObj();

				auto& epos = priv::TransformSystem::TransformableComponents.at(entityid).position;
				m_engine.GetCamera()->SetPosition(Vec3f(epos.x, epos.y, 10.0f));

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
				m_entity_mgr->SaveEntityAsTemplate(&m_entity_mgr->GetEntities().at(e.second));
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
				m_entity_mgr->SetCurrentEntity(&m_entity_mgr->GetEntities().at(e.second));
				m_comp_mgr->SetCurrentEntity(&m_entity_mgr->GetEntities().at(e.second));
				m_comp_mgr->SetCurrentComponent(COMPONENT_TYPE::TRANSFORMABLE, m_entity_mgr->GetEntities().at(e.second).id);
				//Inform GuiCompMgr that json object pointing to current component has been invalidated
				m_gui_comp_mgr->InvalidateComponentObj();
				elem_visibility::show_component_mgr_window = true;

				auto& epos = priv::TransformSystem::TransformableComponents.at(m_entity_mgr->GetCurrentEntity()->id).position;
				m_engine.GetCamera()->SetPosition(Vec3f(epos.x, epos.y, 10.0f));
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
				m_entity_mgr->DeleteEntityOnEditor(e.first);
				break;
			}
		}
	}

	ImGui::End();
}

}//namespace gui
}//namespace se