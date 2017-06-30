#include <managers/SceneManager.h>
#include <imgui/imgui.h>
#include <core/Engine.h>

namespace se
{
namespace priv
{
SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Update(bool showGUIwindow)
{
	if (showGUIwindow)
	{
		//Imgui test variables
		bool show_test_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImColor(114, 144, 154);


		// 1. Show a simple window
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		{
			ImGui::Begin("SceneManager");
			if (ImGui::CollapsingHeader("Create scene"))
			{
				ImGui::Text("Scene name:");
				char scenename[32] = "";
				ImGui::InputText("", scenename, sizeof(char)*32, ImGuiInputTextFlags_CharsNoBlank);
				
				static bool scenetype_menu = false;
				static bool scenetype_level = false;
				static bool scenetype_credits = false;

				ImGui::Text("Scene type");
				ImGui::Checkbox("Menu", &scenetype_menu);
				ImGui::Checkbox("Level", &scenetype_level);
				ImGui::Checkbox("Credits", &scenetype_credits);
				
			}
			if (ImGui::CollapsingHeader("Load scene"))
			{
			
			}
			//ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("Movement editor editor")) show_test_window ^= 1;
			if (ImGui::Button("Component editor")) show_another_window ^= 1;
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
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

void SceneManager::SaveScene()
{
	//Save scene to json
}

void SceneManager::LoadScene(std::string scenename)
{

}

void SceneManager::DeleteScene(std::string scenename)
{

}

}//namespace priv
}//namespace se