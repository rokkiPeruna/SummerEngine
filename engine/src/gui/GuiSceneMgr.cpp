#include <gui/GuiSceneMgr.h>
#include <managers/Scene.h>

namespace se
{
namespace gui
{
GuiSceneMgr::GuiSceneMgr(priv::Engine& engine_ref)
	: ManagerGui(engine_ref)
	, m_sceneMgr(nullptr)
	, m_gui_sceneAdded(false)
	, m_gui_addSceneNameConflict(false)
	, m_gui_sceneAlreadyLoaded(false)

{
	m_sceneMgr = &m_engine.GetSceneMgr();
}

GuiSceneMgr::~GuiSceneMgr()
{

}

void GuiSceneMgr::Update()
{
	assert(m_sceneMgr);

	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(win_width / 2, win_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("SceneManager", &show_scene_mgr_window);

	if (ImGui::CollapsingHeader("Create scene"))
	{
		ImGui::Text("Scene name:");
		static SEchar scenename[64];
		ImGui::InputText("", scenename, 64, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(scenename) != 0)
		{
			ImGui::Text("Scene type");
			static SEint scenetype_picker = 0;
			ImGui::RadioButton("Menu", &scenetype_picker, static_cast<SEint>(priv::SCENE_TYPE::MENU)); ImGui::SameLine();
			ImGui::RadioButton("Level", &scenetype_picker, static_cast<SEint>(priv::SCENE_TYPE::LEVEL)); ImGui::SameLine();
			ImGui::RadioButton("Credits", &scenetype_picker, static_cast<SEint>(priv::SCENE_TYPE::CREDITS));

			static SEint width = 0;
			static SEint heigth = 0;
			if (scenetype_picker == static_cast<SEint>(priv::SCENE_TYPE::LEVEL))
			{
				ImGui::Separator();
				ImGui::SliderInt("Level width", &width, 2, 128);
				ImGui::SliderInt("Level heigth", &heigth, 2, 128);
			}

			if (scenetype_picker != 0 && std::strlen(scenename) != 0)
			{
				ImGui::Separator();
				if (ImGui::Button("Add scene"))
				{
					if (!m_sceneMgr->AddScene(scenename, static_cast<priv::SCENE_TYPE>(scenetype_picker), width, heigth))
						m_gui_addSceneNameConflict = true;
					else
						m_gui_sceneAdded = true;
				}
			}
		}
	}
	if (ImGui::CollapsingHeader("Load scene"))
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Scene list"))
		{
			ImGui::Separator();
			for (auto sn : m_sceneMgr->GetSceneNames())
			{
				ImGui::Bullet();
				if (ImGui::SmallButton(sn.c_str()))
				{
					if (!m_sceneMgr->LoadScene(sn))
						m_gui_sceneAlreadyLoaded = true;
				}
			}
			ImGui::TreePop();
		}
	}
	if (ImGui::Button("SAVE CURRENT PROGRESS"))
	{
		m_sceneMgr->SaveProgress();
	}

	_handlePopups();
	ImGui::End();
}

void GuiSceneMgr::_handlePopups()
{
	if (m_gui_addSceneNameConflict)
	{
		ImGui::OpenPopup("Name conflict!");
		if (ImGui::BeginPopupModal("Name conflict!", &m_gui_addSceneNameConflict, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
		{
			ImGui::Separator();
			ImGui::Text("Scene with given name already exists!\nChange the name.");
			if (ImGui::Button("OK"))
			{
				m_gui_addSceneNameConflict = false;
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::EndPopup();
	}
	if (m_gui_sceneAdded)
	{
		ImGui::OpenPopup("");
		if (ImGui::BeginPopupModal("", &m_gui_sceneAdded, ImGuiWindowFlags_Modal | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
		{
			ImGui::Separator();
			ImGui::Text("Scene added successfully!");
			if (ImGui::Button("OK"))
			{
				m_gui_sceneAdded = false;
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::EndPopup();
	}
	if (m_gui_sceneAlreadyLoaded)
	{
		ImGui::OpenPopup("");
		if (ImGui::BeginPopupModal("", &m_gui_sceneAlreadyLoaded, ImGuiWindowFlags_Modal | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
		{
			ImGui::Separator();
			ImGui::Text("Scene already loaded to memory\n OR something failed. Check console!");
			if (ImGui::Button("OK"))
			{
				m_gui_sceneAlreadyLoaded = false;
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::EndPopup();
	}
}

}//namespace gui
}//namespace se