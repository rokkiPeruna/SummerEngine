#include <managers/SceneManager.h>
#include <imgui/imgui.h>
#include <core/Engine.h>
#include <core/Messages.h>
#include <nlohmann_json/json.hpp>

namespace se
{
namespace priv
{
SceneManager::SceneManager()
	: m_rel_filep_scenes("")
	, m_scenes{}
	, m_sceneNames{}
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize(std::string filepath_to_json_scenes)
{
	///Relative path to scenes.json file
	m_rel_filep_scenes = filepath_to_json_scenes;

	///Load scene names
	_loadSceneNames();
}

void SceneManager::Uninitialize()
{

}

void SceneManager::Update(bool showGUIwindow)
{
	if (showGUIwindow)
	{
		_updateGUI();
	}

}

void SceneManager::AddScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	//Check for name conflicts
	for (auto sn : m_sceneNames)
	{
		if (scenename == sn)
		{
			MessageWarning(SceneMgr_id) << "Scene with name " + scenename + " already exists, scene not added to scenes.json";
			return;
		}
	}
	//If name is valid, add scene to scenes.json and add it name to m_sceneNames
	std::ofstream scenes(m_rel_filep_scenes + "scenes.json", std::ios::app);
	if (scenes.is_open())
	{
		//SE_TODO: Make this cleverer
		std::string type_as_string;
		if (type == SCENE_TYPE::MENU) type_as_string = "menu";
		else if (type == SCENE_TYPE::LEVEL) type_as_string = "level";
		else if (type == SCENE_TYPE::CREDITS) type_as_string = "credits";
		else type_as_string = "faulty_type";

		nlohmann::json newScene = {
			{"name", scenename},
			{"type", type_as_string},
			{"width", width},
			{"heigth", heigth},
			{"entity_ids", 0} //No entities at adding
		};
		scenes << std::setw(4) << newScene << std::endl;
	}
	else
	{
		MessageWarning(SceneMgr_id) << "Failed to open scenes.json in AddScene, scene not added";
		return;
	}


}

void SceneManager::SaveScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	

}

void SceneManager::LoadScene(std::string scenename)
{

}

void SceneManager::DeleteScene(std::string scenename)
{

}

void SceneManager::_loadSceneNames()
{
	///Load all scenes from scenes.json file
	nlohmann::json loader;
	std::ifstream data(m_rel_filep_scenes + "/scenes.json");
	if (data.is_open())
	{
		loader = nlohmann::json::parse(data);
		data.close();

		if(loader.find("scenes") != loader.end())
		for (auto itr = loader["scenes"].begin(); itr != loader["scenes"].end(); itr++)
		{
			m_sceneNames.emplace_back(itr.key());
		}
	}
	else
	{
		MessageError(SceneMgr_id) << "Failed to load and parse scenes.json in _loadSceneNames()";
	}
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
			ImGui::SliderInt("Level heigth", &heigth, 2, 128);
		}

		//Save created scene
		if (scenetype_picker != 0 && scenename != "")
		{
			ImGui::Separator();
			if (ImGui::Button("Add scene"))
			{
				AddScene(scenename, static_cast<SCENE_TYPE>(scenetype_picker), width, heigth);
			}
		}

	}
	//Load scene from json
	if (ImGui::CollapsingHeader("Load scene"))
	{
		ImGui::Separator();
		ImGui::Text("Scene list");
		//Add scene names to list to choose from
		std::vector<bool> selected;
		for (auto sn : m_sceneNames)
		{
			selected.emplace_back(false);
			ImGui::Selectable(sn.c_str(), selected.back());
		}
	}
	ImGui::End();

}

}//namespace priv
}//namespace se