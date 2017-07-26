#include <gui/GuiCompMgr.h>
#include <core/Engine.h>

namespace se
{
namespace gui
{
GuiCompMgr::GuiCompMgr()
	: m_entity_mgr(nullptr)
	, m_comp_mgr(nullptr)
{
	m_entity_mgr = priv::Engine::Instance().GetEntityMgr();
	m_comp_mgr = priv::Engine::Instance().GetCompMgr();
}

GuiCompMgr::~GuiCompMgr()
{
	m_entity_mgr = nullptr;
	m_comp_mgr = nullptr;
}

void GuiCompMgr::Update()
{
	assert(m_entity_mgr);
	assert(m_comp_mgr);

	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(gui::_gui_width / 2, gui::_gui_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Component Editor", &gui::_gui_show_component_mgr_window);

	auto curr_e = m_entity_mgr->GetCurrentEntity();
	if (curr_e)
		ImGui::Text(curr_e->name.c_str());
	else
	{
		//If no active entity, skip rest
		ImGui::Text("NO ACTIVE ENTITY");
		ImGui::End();
		return;
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Add component"))
	{
		for (auto& component : priv::CompTypeAsString)
		{
			if (curr_e->components.count(component.first))
				continue;

			if (ImGui::Button(component.second.c_str()))
			{
				m_comp_mgr->AddNewComponentToEntity(*curr_e, component.first);
			}
		}
	}
	if (ImGui::CollapsingHeader("Remove component"))
	{
		for (auto& component : curr_e->components)
		{
			//Can't delete position component
			if (component.first == COMPONENT_TYPE::TRANSFORMABLE)
				continue;
			if (ImGui::Button(priv::CompTypeAsString.at(component.first).c_str()))
			{
				m_comp_mgr->RemoveComponentFromEntity(*curr_e, component.first);
				break;
			}
		}
	}
	if (ImGui::CollapsingHeader("Modify component"))
	{
		for (auto& component : curr_e->components)
		{
			if (ImGui::Button(priv::CompTypeAsString.at(component.first).c_str()))
			{
				m_comp_mgr->SetCurrentComponent(component.first, component.second);
				break;
			}
		}
		if (curr_e && m_comp_mgr->GetCurrentComponent())
		{
			m_comp_mgr->ModifyComponentFromEntity();
		}
	}

	ImGui::End();
}

}//namespace gui
}//namespace se