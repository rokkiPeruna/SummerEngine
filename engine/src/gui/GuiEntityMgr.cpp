#include <gui/GuiEntityMgr.h>
#include <core/Engine.h>

namespace se
{
namespace gui
{
GuiEntityMgr::GuiEntityMgr()
	: m_entity_mgr(nullptr)
	, m_comp_mgr(nullptr)
	, m_gui_scene_name("NO ACTIVE SCENE")
{
	m_entity_mgr = priv::Engine::Instance().GetEntityMgr();
	m_comp_mgr = priv::Engine::Instance().GetCompMgr();
}

GuiEntityMgr::~GuiEntityMgr()
{
	m_entity_mgr = nullptr;
	m_comp_mgr = nullptr;
}

void GuiEntityMgr::Update()
{
	assert(m_entity_mgr);
	assert(m_comp_mgr);

	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(_gui_width / 2, _gui_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Entity editor", &_gui_show_entity_comp_mgr_window); ImGui::SameLine();
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
		static SEchar entityname[64];
		ImGui::InputText("Name", entityname, 64, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(entityname) != 0)
		{
			if (ImGui::Button("Create!"))
			{
				m_entity_mgr->CreateEntityOnEditor(entityname);
				memset(&entityname[0], 0, sizeof(entityname));
			}
		}

	}
	if (ImGui::CollapsingHeader("Delete entity"))
	{
		for (auto& e : m_entity_mgr->GetEntities())
		{
			if (ImGui::Button(e.first.c_str()))
			{
				m_entity_mgr->DeleteEntityOnEditor(e.first);
				break;
			}
		}
	}
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Entities"))
	{
		for (auto& e : m_entity_mgr->GetEntities())
		{
			ImGui::Bullet();
			if (ImGui::SmallButton(e.second.name.c_str()))
			{
				m_entity_mgr->SetCurrentEntity(&e.second);
				m_comp_mgr->SetCurrentEntity(&e.second);
				_gui_show_component_mgr_window = true;
			}
		}
	}
	ImGui::End();
}

}//namespace gui
}//namespace se