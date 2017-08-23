#include <gui/GuiSceneMgr.h>
#include <managers/Scene.h>

namespace se
{
namespace gui
{
GuiSceneMgr::GuiSceneMgr(priv::Engine& engine_ref, SEuint update_priority)
	: ManagerGui(engine_ref, update_priority)
	, m_sceneMgr(nullptr)
{
	m_sceneMgr = &m_engine.GetSceneMgr();
}

void GuiSceneMgr::Update()
{
	assert(m_sceneMgr);

	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(window_data::width / 2.0f, window_data::heigth / 2.0f), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("SceneManager", &elem_visibility::show_scene_mgr_window);

	ImGui::Text("Create scene");
	{
		ImGui::Text("Scene name:");
		static SEchar scenename[32];
		ImGui::InputText("", scenename, 32, ImGuiInputTextFlags_CharsNoBlank);
		if (std::strlen(scenename) != 0)
		{
			static SEint width = 0;
			static SEint heigth = 0;
			ImGui::Separator();
			ImGui::SliderInt("Width", &width, 2, 128);
			ImGui::SliderInt("Heigth", &heigth, 2, 128);
			if (std::strlen(scenename) != 0)
			{
				ImGui::Separator();
				if (ImGui::Button("Add scene"))
				{
					m_event_handler.SendEvent(SE_Event_SceneCreatedOnEditor(scenename, width, heigth));
				}
			}
		}
	}
	if (ImGui::TreeNode("Load scene"))
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
					char sname[32];
					memcpy(sname, sn.c_str(), sizeof(sname));
					m_event_handler.SendEvent(SE_Cmd_LoadScene(sname));				
				}
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
}

}//namespace gui
}//namespace se