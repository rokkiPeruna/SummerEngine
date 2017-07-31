#include <gui/GuiCompMgr.h>
#include <core/Engine.h>
#include <nlohmann_json/json.hpp>

namespace se
{
namespace gui
{
GuiCompMgr::GuiCompMgr()
	: m_scene_mgr(nullptr)
	, m_entity_mgr(nullptr)
	, m_comp_mgr(nullptr)
	, m_reInitWithNewComp(true)
	, m_component_obj()
	, m_curr_component(nullptr)
	, m_curr_comp_index(-1)
{
	m_scene_mgr = priv::Engine::Instance().GetSceneMgr();
	m_entity_mgr = priv::Engine::Instance().GetEntityMgr();
	m_comp_mgr = priv::Engine::Instance().GetCompMgr();
	assert(m_scene_mgr && m_entity_mgr && m_comp_mgr);
}

GuiCompMgr::~GuiCompMgr()
{
	m_scene_mgr = nullptr;
	m_entity_mgr = nullptr;
	m_comp_mgr = nullptr;
	m_curr_component = nullptr;
}

void GuiCompMgr::Update()
{

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
				m_curr_component = m_comp_mgr->GetCurrentComponent();
				m_curr_comp_index = m_comp_mgr->GetCurrentComponentIndex();
				m_reInitWithNewComp = true;
				break;
			}
		}
		if (m_reInitWithNewComp && m_curr_component)
		{
			_initWithNewComp();
			m_reInitWithNewComp = false;
		}
		if (curr_e && m_curr_component && m_curr_comp_index != -1)
		{
			priv::Engine::ComponentTypeToGuiEditor.at(m_curr_component->type)->ModifyComponent(m_curr_component->type, m_curr_comp_index, m_component_obj);
		}
	}

	ImGui::End();
}

void GuiCompMgr::InvalidateComponentObj()
{
	m_component_obj = {};
	m_reInitWithNewComp = true;
}

void GuiCompMgr::_initWithNewComp()
{
	//SE_TODO: Change this so that we don't need to read json file to get component object on every frame

	auto json = m_scene_mgr->GetCurrentScene()->GetData();
	auto& entities_obj = json->find("entities"); //SE_TODO: Change to some constant
	if (entities_obj == json->end())
	{
		MessageWarning(gui_Manager) << "Failed to find [entities] json object in GuiCompMgr::_initWithNewComp()";
		return;
	}
	auto& entity_obj = entities_obj.value().find(m_entity_mgr->GetCurrentEntity()->name);
	if (entity_obj == entities_obj.value().end())
	{
		MessageWarning(gui_Manager) << "Failed to find " + m_entity_mgr->GetCurrentEntity()->name + " json object in GuiCompMgr::_initWithNewComp()";
		return;
	}
	m_component_obj = entity_obj.value().find(priv::CompTypeAsString.at(m_curr_component->type));
	if (m_component_obj == entity_obj.value().end())
	{
		MessageWarning(gui_Manager) << "Failed to find " + priv::CompTypeAsString.at(m_curr_component->type) + " json object in GuiCompMgr::_initWithNewComp()";
		return;
	}
	//m_component_obj = &component_obj;
	m_curr_comp_index = m_comp_mgr->GetCurrentComponentIndex();
}

}//namespace gui
}//namespace se