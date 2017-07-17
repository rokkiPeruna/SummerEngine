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
	, m_sceneJsonObject()
	, m_sceneNamesJsonObject()
	, m_rel_path_to_json_scenes("")
	, m_scenes_subfolder_name("scenes/")
	, m_scene_file_suffix(".json")
	, m_scene_name_list_file("scenenamelist.json")
	, m_scene_names_json_obj("scenenamelist")
	, m_scene_struct_info_obj_name("scene_info")
	, m_scene_struct_main_obj_name("entities")
	, m_currentScene("", SCENE_TYPE::FAULTY, 0, 0)
	, m_sceneNames{}
	, m_gui_sceneAdded(false)
	, m_gui_addSceneNameConflict(false)
	, m_gui_sceneAlreadyLoaded(false)
{

}

SceneManager::~SceneManager()
{
	m_ecm_ptr = nullptr;
}

void SceneManager::Initialize(const std::string& filepathToUserFiles, EntityManager* ecm_ptr)
{
	///Relative path to scenes.json file
	m_rel_path_to_json_scenes = filepathToUserFiles + m_scenes_subfolder_name;

	///EntityComponentManager pointer
	m_ecm_ptr = ecm_ptr;

	///Load scene names
	_loadSceneNames();
}

void SceneManager::Uninitialize()
{

}

void SceneManager::Update()
{

}

void SceneManager::ShowAndUpdateGUI()
{
	ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(_gui_width / 2, _gui_heigth / 2), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("SceneManager", &_gui_show_scene_mgr_window);

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

			static SEint width = 0;
			static SEint heigth = 0;
			if (scenetype_picker == static_cast<SEint>(SCENE_TYPE::LEVEL))
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
					m_gui_sceneAdded = AddScene(scenename, static_cast<SCENE_TYPE>(scenetype_picker), width, heigth);
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
			for (auto sn : m_sceneNames)
			{
				ImGui::Bullet();
				if (ImGui::SmallButton(sn.c_str()))
				{
					LoadScene(sn);
				}
			}
			ImGui::TreePop();
		}
	}
	if (ImGui::Button("SAVE CURRENT PROGRESS"))
	{
		SaveProgress();
	}

	_handlePopups();
	ImGui::End();
}

bool SceneManager::AddScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	//Check for name conflicts
	for (auto& n : m_sceneNames)
	{
		if (n == scenename)
		{
			MessageWarning(SceneMgr_id) << "Scene with name " + scenename + " already exists, scene not added";
			m_gui_addSceneNameConflict = true;
			return false;
		}
	}

	//If name passes, create a new file with std::ofstream
	std::ofstream newScene(m_rel_path_to_json_scenes + scenename + m_scene_file_suffix);
	if (!newScene.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to create new scene file[" + scenename + "],\nin AddScene, scene not added, returning";
		return false;
	}
	_createStructToNewScene(newScene, scenename, type, width, heigth);
	newScene.close();

	//Rewrite m_scene_name_list_file
	m_sceneNamesJsonObject.clear(); //SE_TODO: Is there need to rewrite the object??
	if (!_readFileToJson(m_sceneNamesJsonObject, m_rel_path_to_json_scenes + m_scene_name_list_file))
		return false;

	auto& names_obj = m_sceneNamesJsonObject.find(m_scene_names_json_obj);

	if (names_obj == m_sceneNamesJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object" + m_scene_names_json_obj + ",\n, scene name not added to " +
			m_scene_names_json_obj + ", removing scene file, scene not added";
		std::remove((m_rel_path_to_json_scenes + scenename + m_scene_file_suffix).c_str());
		return false;
	}
	names_obj.value().push_back(scenename);
	_rewriteFile(m_sceneNamesJsonObject, m_rel_path_to_json_scenes + m_scene_name_list_file);

	//Add name to runtime container
	m_sceneNames.emplace_back(scenename);

	m_gui_sceneAdded = true;

	return true;
}

void SceneManager::SaveScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{


}

void SceneManager::LoadScene(std::string scenename)
{
	if (scenename == m_currentScene.GetName())
	{
		MessageInfo(SceneMgr_id) << "Scene already loaded to memory!";
		m_gui_sceneAlreadyLoaded = true;
		return;
	}
	m_sceneJsonObject.clear(); //SE_TODO: Is there need to rewrite the object??
	if (!_readFileToJson(m_sceneJsonObject, m_rel_path_to_json_scenes + scenename + m_scene_file_suffix))
		return;
	
	//Read scene's info to json object and create new current scene
	auto& info_obj = m_sceneJsonObject.find(m_scene_struct_info_obj_name);
	if (info_obj == m_sceneJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object " + m_scene_struct_info_obj_name + "\nin LoadScene, scene not loaded!";
		return;
	}	
	auto& name = info_obj.value().at("name");
	SEint type_as_int = info_obj.value().at("type");
	auto& w = info_obj.value().at("width");
	auto& h = info_obj.value().at("heigth");
	m_currentScene = { 
		name,
		static_cast<SCENE_TYPE>(type_as_int),
		w, h
	};
	//Check that m_scene_struct_main_obj_name is valid a
	auto& main_obj = m_sceneJsonObject.find(m_scene_struct_main_obj_name);
	if (main_obj == m_sceneJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Could not find " + m_scene_struct_main_obj_name + " in " + scenename + m_scene_file_suffix + "\n, scene not loaded!";
		return;
	}
	//And if it is, give it to m_currentScene, empty systems component containers and init new scene
	m_currentScene.SetData(&m_sceneJsonObject);

	for (auto& s : Engine::Instance().GetSystemsContainer())
	{
		s->ClearComponentContainers();
	}

	m_ecm_ptr->InitWithNewScene(&m_currentScene);
}

void SceneManager::DeleteScene(std::string scenename)
{
	//SE_TODO: Logic!
}

void SceneManager::SaveProgress()
{
	if (m_currentScene.GetType() == SCENE_TYPE::FAULTY)
		return;
	std::string path = m_rel_path_to_json_scenes;
	path += m_currentScene.GetName();
	path += m_scene_file_suffix;
	std::ofstream file(path, std::ios::trunc);
	if (!file.is_open())
	{
		MessageError(EntityMgr_id) << "Failed to open " + m_rel_path_to_json_scenes + m_currentScene.GetName() + "\n, entities not saved";
		return;
	}
	file << std::setw(4) << *m_currentScene.GetData() << std::endl;
}

bool SceneManager::_readFileToJson(nlohmann::json& j, std::string& filepath)
{
	std::ifstream data(filepath);
	if (!data.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to open " + filepath + " for\nreading in _readFileToJson()";
		return false;
	}
	j = nlohmann::json::parse(data);
	data.close();
	return true;
}

bool SceneManager::_rewriteFile(nlohmann::json& j, std::string& filepath)
{
	std::ofstream file(filepath, std::ios::trunc);
	if (!file.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to open " + filepath + " for rewriting in _rewriteFile()";
		return false;
	}
	else
	{
		file << std::setw(4) << j << std::endl;
		file.close();
		return true;
	}
	return false;
}

void SceneManager::_loadSceneNames()
{
	std::ifstream data(m_rel_path_to_json_scenes + m_scene_name_list_file);
	if (!data.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to open " + m_rel_path_to_json_scenes + m_scene_name_list_file + "\n for reading, no scenes loaded, returning";
		return;
	}
	//Check if m_scene_name_list_file is empty //SE_TODO: Better way to check emptiness exists
	if (data.peek() == std::ifstream::traits_type::eof())
	{
		MessageInfo(SceneMgr_id) << m_scene_name_list_file + " is empty, no basic json structure available, creating json structure";
		_createStructToScnNamesJson();
		return;
	}
	nlohmann::json j = nlohmann::json::parse(data);

	auto& names_obj = j.find(m_scene_names_json_obj);
	if (names_obj == j.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object " + m_scene_names_json_obj + " in " + m_scene_name_list_file + ",\nscenes not loaded";
		return;
	}
	for (auto& n : names_obj.value())
	{
		std::string t = n;
		m_sceneNames.emplace_back(t);
	}
}

void SceneManager::_createStructToNewScene(std::ofstream& file, std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	std::string typestr = std::to_string(static_cast<SEuint>(type));
	std::string w = std::to_string(width);
	std::string h = std::to_string(heigth);
	file << "{\n" <<
		"\"" + m_scene_struct_info_obj_name + "\":{\n" <<
		"\t\"name\":\"" + scenename + "\",\n" <<
		"\t\"type\":" + typestr + ",\n" <<
		"\t\"width\":" + w + ",\n" <<
		"\t\"heigth\":" + h + "\n" <<
		"},\n"
		"\"" + m_scene_struct_main_obj_name + "\":{\n" <<
		"  }\n" <<
		"}" << std::endl;
}

void SceneManager::_createStructToScnNamesJson()
{
	std::ofstream data(m_rel_path_to_json_scenes + m_scene_name_list_file);
	if (!data.is_open())
	{
		MessageWarning(SceneMgr_id) << "Failed to open " + m_scene_name_list_file + " in _createStructToScnNamesJson()";
		return;
	}
	//
	data << "{\n" <<
		"\"" + m_scene_names_json_obj + "\":[\n" <<
		"  ]\n" <<
		"}" << std::endl;
	data.close();
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