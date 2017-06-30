#include <managers/SceneManager.h>
#include <imgui/imgui.h>
#include <core/Engine.h>

namespace se
{
namespace priv
{
SceneManager::SceneManager()
	: m_scenes{}
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Update(bool showGUIwindow)
{
	if (showGUIwindow)
	{
		_updateGUI();
	}

}

void SceneManager::AddScene(std::string scenename, SCENE_TYPE type)
{
	//Check names for possible conflicts
	//for (auto& s : m_scenes)
	//{
	//	if (s.GetName() == scenename)
	//	{
	//		//TODO: Send message
	//		return;
	//	}
	//}
	////If there is no name conflict, add scene to container
	//m_scenes.emplace_back(Scene(scenename, type));
	std::cout << "scene " << scenename << " added" << std::endl;

}

void SceneManager::SaveScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	//Save scene to json
}

void SceneManager::LoadScene(std::string scenename)
{

}

void SceneManager::DeleteScene(std::string scenename)
{

}

void SceneManager::_updateGUI()
{

	ImGui::SetNextWindowSize(ImVec2(300.f, 300.f), ImGuiSetCond_Appearing);
	ImGui::Begin("SceneManager", &_gui_show_scene_mgr_window);
	if (ImGui::CollapsingHeader("Create scene"))
	{
		ImGui::Text("Scene name:");
		static SEchar scenename[64];
		ImGui::InputText("", scenename, 64, ImGuiInputTextFlags_CharsNoBlank);

		ImGui::Text("Scene type");
		static SEint scenetype_picker = 0;
		ImGui::RadioButton("Menu", &scenetype_picker, static_cast<SEint>(SCENE_TYPE::MENU)); ImGui::SameLine();
		ImGui::RadioButton("Level", &scenetype_picker, static_cast<SEint>(SCENE_TYPE::LEVEL)); ImGui::SameLine();
		ImGui::RadioButton("Credits", &scenetype_picker, static_cast<SEint>(SCENE_TYPE::CREDITS));

		//If level is chosen, show level size and other details
		static SEint width = 0;
		static SEint heigth = 0;
		if (scenetype_picker == static_cast<SEint>(SCENE_TYPE::LEVEL))
		{
			ImGui::Separator();
			ImGui::SliderInt("Level width", &width, 2, 128);
			ImGui::SliderInt("Level width", &heigth, 2, 128);
		}

		//Save created scene
		if (scenetype_picker != 0 && scenename != "")
		{
			ImGui::Separator();
			if (ImGui::Button("Save scene"))
			{
				SaveScene(scenename, static_cast<SCENE_TYPE>(scenetype_picker), width, heigth);
			}
		}

	}
	//Load scene from json
	if (ImGui::CollapsingHeader("Load scene"))
	{

	}
	ImGui::End();

}

}//namespace priv
}//namespace se