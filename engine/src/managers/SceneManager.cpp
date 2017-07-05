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
	: m_ecm_ptr(nullptr)
	, m_rel_filep_scenes("")
	, m_scenes_json_file_name("scenes.json")
	, m_scenes{}
	, m_currentScene(nullptr)
	, m_sceneNamesAndIDs{}
	, m_curr_largest_sceneid(0)
	, m_gui_width(300.f)
	, m_gui_heigth(300.f)
	, m_gui_sceneAdded(false)
	, m_gui_addSceneNameConflict(false)
	, m_gui_sceneAlreadyLoaded(false)
{

}

SceneManager::~SceneManager()
{
	m_ecm_ptr = nullptr;
	m_currentScene = nullptr;
}

void SceneManager::Initialize(const std::string& filepath_to_json_scenes, EntityComponentManager* ecm_ptr)
{
	///Relative path to scenes.json file
	m_rel_filep_scenes = filepath_to_json_scenes;

	///EntityComponentManager pointer
	m_ecm_ptr = ecm_ptr;

	///Load scene names
	_loadSceneNamesAndIDs();
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


bool SceneManager::AddScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	//Check for name conflicts
	if (m_sceneNamesAndIDs.find(scenename) != m_sceneNamesAndIDs.end())
	{
		MessageWarning(SceneMgr_id) << "Scene with name " + scenename + " already exists, scene not added to scenes.json";
		m_gui_addSceneNameConflict = true;
		return false;
	}
	//If name is valid, add scene to scenes.json and add it's name to m_sceneNames
	std::ifstream scenes(m_rel_filep_scenes + m_scenes_json_file_name);
	if (!scenes.is_open())
	{
		MessageWarning(SceneMgr_id) << "Failed to open scenes.json in AddScene(), scene not added, returning..";
		return false;
	}
	//SE_TODO: Make this cleverer?
	std::string type_as_string;
	if (type == SCENE_TYPE::MENU) type_as_string = "menu";
	else if (type == SCENE_TYPE::LEVEL) type_as_string = "level";
	else if (type == SCENE_TYPE::CREDITS) type_as_string = "credits";
	else type_as_string = "faulty_type";

	auto& main_obj = nlohmann::json::parse(scenes);
	scenes.close();
	auto& scenes_obj = main_obj.find("scenes");
	if (scenes_obj == main_obj.end())
	{
		MessageWarning(SceneMgr_id) << "Failed to open scenes.json in AddScene, scene not added";
		return false;
	}

	const char* tmpname = scenename.c_str();
	//Push empty object with scenename
	scenes_obj.value().push_back({ tmpname, {} });
	//Take iterator to the newly created scene object
	auto& curr_scene_obj = scenes_obj.value().find(tmpname);
	if (curr_scene_obj == scenes_obj.value().end())
	{
		MessageWarning(SceneMgr_id) << "Failed to find scene object in scenes.json, scene name: " + scenename + ". Returning..";
		return false;
	}
	//Add keys and values to the newly created object
	curr_scene_obj.value() =
	{
			{"name", scenename},
			{"type", type_as_string},
			{"width", width},
			{"heigth", heigth},
			{"id", ++m_curr_largest_sceneid} //Increment m_curr_largest_sceneid before adding it to the new scene!!
	};
	//Open scenes.json for writing with ios::trunc flag so that the main_obj that now contains all old scenes and the newly added scene, overwrites
	//the whole json file. //TODO: This can improved a lot, currently we clear the whole file and rewrite it again
	std::ofstream write(m_rel_filep_scenes + m_scenes_json_file_name, std::ios::out | std::ios::trunc);
	if (!write.is_open())
	{
		MessageWarning(SceneMgr_id) << "Failed to open scenes.json for writing in AddScene(). Scene not added, returning..";
		return false;
	}
	//Write the main_obj (prettified) to the file and add scenename and id to m_sceneNamesAndIDs
	write << std::setw(4) << main_obj << std::endl;
	m_sceneNamesAndIDs.emplace(tmpname, m_curr_largest_sceneid);
	m_gui_sceneAdded = true;
	return true;
}

void SceneManager::SaveScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{


}

void SceneManager::LoadScene(std::string scenename)
{
	///Check if scene with that id is already loaded to m_scenes
	for (auto& s : m_scenes)
	{
		if (s.GetName() == scenename)
		{
			MessageInfo(SceneMgr_id) << "Scene already loaded to memory!";
			m_gui_sceneAlreadyLoaded = true;
			return;
		}
	}
	//Create Scene object
	std::ifstream data(m_rel_filep_scenes + m_scenes_json_file_name);
	if (!data.is_open())
	{
		MessageWarning(SceneMgr_id) << "Could not open scenes.json for reading in LoadScene(). Returning!";
		return;
	}
	nlohmann::json main_obj = nlohmann::json::parse(data);
	data.close();
	//Check that scenes.json has "scenes" object
	if (main_obj.find("scenes") == main_obj.end())
	{
		MessageWarning(SceneMgr_id) << "\"scenes\" object not found in scenes.json in LoadScene(). Scene not loaded to memory, returning.";
		return;
	}
	//Take itr to "scenes" object
	auto& scenes_obj = main_obj.at("scenes");

	//Check that scene with parameter "scenename" can be found
	if (scenes_obj.find(scenename) == scenes_obj.end())
	{
		MessageWarning(SceneMgr_id) << "Could not find scene with name " + scenename + " in LoadScene(). Scene not loaded to memory, returning";
		return;
	}
	auto& loaded_scene_obj = scenes_obj.find(scenename);
	auto& values = loaded_scene_obj.value();
	//Fetch values from json object and emplace scene to m_scenes
	std::string tmpname = values.at("name");

	//SE_TODO: Make this cleverer?
	SCENE_TYPE tmptype;
	std::string type_as_string = values.at("type");
	if (type_as_string == "menu") tmptype = SCENE_TYPE::MENU;
	else if (type_as_string == "level") tmptype = SCENE_TYPE::LEVEL;
	else if (type_as_string == "credits") tmptype = SCENE_TYPE::CREDITS;
	else tmptype = SCENE_TYPE::FAULTY;

	SEint tmpid = values.at("id");
	SEuint tmpwidth = values.at("width");
	SEuint tmpheigth = values.at("heigth");

	m_scenes.emplace_back(Scene(tmpname, tmptype, tmpid, tmpwidth, tmpheigth));
	DebugMessageInfo(SceneMgr_id) << "New scene [" + scenename + "] loaded to memory";
	m_currentScene = &m_scenes.back();

	//Initialize EntityComponentManager with new scene's info
	m_ecm_ptr->InitWithNewScene(m_currentScene);
}

void SceneManager::DeleteScene(std::string scenename)
{

}

void SceneManager::_loadSceneNamesAndIDs()
{
	///Load all scenes from scenes.json file
	nlohmann::json loader;
	std::ifstream data(m_rel_filep_scenes + m_scenes_json_file_name);
	if (data.is_open())
	{
		//Check if scenes.json is empty
		if (data.peek() == std::ifstream::traits_type::eof())
		{
			MessageInfo(SceneMgr_id) << "scenes.json is empty, no basic json structure available, creating json structure";
			_createSceneStructureToJsonFile();
			return;
		}
		loader = nlohmann::json::parse(data);
		data.close();
		//Be sure that "scenes" object exist
		if (loader.find("scenes") != loader.end())
			//Loop all scenes, take their name and id to container
			for (auto itr = loader["scenes"].begin(); itr != loader["scenes"].end(); itr++)
			{
				//Find the "id" value
				if (itr.value().find("id") != itr.value().end())
				{
					m_sceneNamesAndIDs.emplace(itr.key(), itr.value().at("id"));
					//Check if id value is larger than current m_curr_largest_sceneid
					SEuint tmp = itr.value().at("id");
					if (tmp > m_curr_largest_sceneid)
						m_curr_largest_sceneid = tmp;
				}
				//If not found, something is wrong with the scene object
				else
				{
					MessageWarning(SceneMgr_id) << "Scene in scenes.json found with no valid \"id\" value!";
				}
			}
	}
	else
	{
		MessageError(SceneMgr_id) << "Failed to load and parse scenes.json in loadSceneNamesAndIDs()";
	}
}

void SceneManager::_createSceneStructureToJsonFile()
{
	nlohmann::json j;
	std::ofstream data(m_rel_filep_scenes + m_scenes_json_file_name);
	if (data.is_open())
	{
		data << "{\n" <<
			"\"scenes\":{\n" <<
			"  }\n" <<
			"}" << std::endl;
		data.close();
	}
	else
	{
		MessageWarning(SceneMgr_id) << "Failed to open scenes.json in _createSceneStructureToJsonFile()";
	}
}

void SceneManager::_updateGUI()
{
	ImGui::SetNextWindowSize(ImVec2(m_gui_width, m_gui_heigth), ImGuiSetCond_Appearing);
	ImGui::Begin("SceneManager", &_gui_show_scene_mgr_window);

	//Create new scene
	if (ImGui::CollapsingHeader("Create scene"))
	{
		ImGui::Text("Scene name:");
		static SEchar scenename[64];
		ImGui::InputText("", scenename, 64, ImGuiInputTextFlags_CharsNoBlank);

		if (std::strlen(scenename) != 0)
		{

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
					m_gui_sceneAdded = AddScene(scenename, static_cast<SCENE_TYPE>(scenetype_picker), width, heigth);
				}
			}
		}
	}
	//Load scene from json
	if (ImGui::CollapsingHeader("Load scene"))
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Scene list"))
		{
			ImGui::Separator();
			//Add scene names to list to choose from
			for (auto sn : m_sceneNamesAndIDs)
			{
				ImGui::Bullet();
				if (ImGui::SmallButton(sn.first.c_str()))
				{
					LoadScene(sn.first);
				}
			}
			//Check if scenename is double clicked
			//for (SEint i = 0; i < selected.size(); i++)
			//{
			//	if (ImGui::IsMouseDoubleClicked(i))
			//	{
			//		Message(SceneMgr_id) << "Double click!";
			//
			//	}
			//}
			ImGui::TreePop();
		}
	}

	//Handle pop ups
	_handlePopups();

	ImGui::End();
}

void SceneManager::_handlePopups()
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
			ImGui::Text("Scene already loaded to memory!");
			if (ImGui::Button("OK"))
			{
				m_gui_sceneAlreadyLoaded = false;
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::EndPopup();
	}
}

}//namespace priv
}//namespace se