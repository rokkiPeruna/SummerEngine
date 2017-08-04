#include <managers/SceneManager.h>
//#include <imgui/imgui.h>
#include <core/Engine.h>
#include <core/Messages.h>
#include <utility/JsonUtilFunctions.h>

namespace se
{
namespace priv
{
SceneManager::SceneManager(Engine* engine_ptr)
	: Manager(engine_ptr)
	, m_entity_mgr(nullptr)
	, m_comp_mgr(nullptr)
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
{

}

SceneManager::~SceneManager()
{
	m_entity_mgr = nullptr;
	m_comp_mgr = nullptr;
}

void SceneManager::Initialize(const std::string& filepathToUserFiles, EntityManager* entityMgr_ptr, ComponentManager* compMgr_ptr)
{
	///Relative path to scenes.json file
	m_rel_path_to_json_scenes = filepathToUserFiles + m_scenes_subfolder_name;

	///EntityComponentManager pointer
	m_entity_mgr = entityMgr_ptr;

	///ComponentManager pointer
	m_comp_mgr = compMgr_ptr;

	assert(m_entity_mgr && m_comp_mgr);

	///Load scene names
	_loadSceneNames();
}

void SceneManager::Uninitialize()
{

}

void SceneManager::Update()
{

}

SEbool SceneManager::AddScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{
	//Check for name conflicts
	for (auto& n : m_sceneNames)
	{
		if (n == scenename)
		{
			MessageWarning(SceneMgr_id) << "Scene with name " + scenename + " already exists, scene not added";
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
	try { util::ReadFileToJson(m_sceneNamesJsonObject, m_rel_path_to_json_scenes + m_scene_name_list_file, SceneMgr_id); }
	catch (const se_exc_file_open_failed& exc)
	{
		MessageError(SceneMgr_id) << exc.msg + ",\nreturning, scene not added, delete empty file in scene folder";
		return false;
	}
	catch (const se_exc_json_parse_failed& exc)
	{
		MessageError(SceneMgr_id) << exc.msg + ",\nreturning, scene not added, delete empty file in scene folder";
		return false;
	}


	auto& names_obj = m_sceneNamesJsonObject.find(m_scene_names_json_obj);

	if (names_obj == m_sceneNamesJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object" + m_scene_names_json_obj + ",\n, scene name not added to " +
			m_scene_names_json_obj + ", removing scene file, scene not added";
		std::remove((m_rel_path_to_json_scenes + scenename + m_scene_file_suffix).c_str());
		return false;
	}
	names_obj.value().push_back(scenename);

	util::RewriteFileWithJson(m_sceneNamesJsonObject, m_rel_path_to_json_scenes + m_scene_name_list_file, SceneMgr_id);

	//Add name to runtime container
	m_sceneNames.emplace_back(scenename);

	return true;
}

void SceneManager::SaveScene(std::string scenename, SCENE_TYPE type, SEint width, SEint heigth)
{


}

SEbool SceneManager::LoadScene(std::string scenename, SEbool reinitialization)
{
	if (scenename == m_currentScene.GetName() && !reinitialization)
	{
		MessageInfo(SceneMgr_id) << "Scene already loaded to memory!";
		return false;
	}
	m_sceneJsonObject.clear();

	try { util::ReadFileToJson(m_sceneJsonObject, m_rel_path_to_json_scenes + scenename + m_scene_file_suffix, SceneMgr_id); }
	catch (const se_exception& exc)
	{
		MessageError(SceneMgr_id) << "Failed to parse [" + scenename + "] json object or failed to open\nfile " + m_rel_path_to_json_scenes + scenename + m_scene_file_suffix
			+ ",\nexception message: " + exc.msg;
		return false;
	}

	//Read scene's info to json object and create new current scene
	auto& info_obj = m_sceneJsonObject.find(m_scene_struct_info_obj_name);
	if (info_obj == m_sceneJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object " + m_scene_struct_info_obj_name + "\nin LoadScene, scene not loaded!";
		return false;
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
	//Check that m_scene_struct_main_obj_name is valid
	auto& main_obj = m_sceneJsonObject.find(m_scene_struct_main_obj_name);
	if (main_obj == m_sceneJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Could not find " + m_scene_struct_main_obj_name + " in " + scenename + m_scene_file_suffix + "\n, scene not loaded!";
		return false;
	}
	//And if it is, give it to m_currentScene, empty systems component containers and init new scene
	m_currentScene.SetData(&m_sceneJsonObject);

	for (auto& s : m_engine->GetSystemsContainer())
	{
		s->ClearComponentContainers();
	}

	m_entity_mgr->InitWithNewScene(&m_currentScene);
	return true;
}

void SceneManager::ReinitScene()
{
	if (m_currentScene.GetType() != SCENE_TYPE::FAULTY)
	{
		LoadScene(m_currentScene.GetName(), true);
		m_entity_mgr->SetCurrentEntity(nullptr);
		m_comp_mgr->SetCurrentEntity(nullptr);
		m_comp_mgr->SetCurrentComponent(COMPONENT_TYPE::FAULTY_TYPE, -1);
	}
}

void SceneManager::DeleteScene(std::string scenename)
{
	//SE_TODO: Logic!
}

void SceneManager::SaveProgress()
{
	if (m_currentScene.GetType() == SCENE_TYPE::FAULTY)
		return;

	std::ofstream file(m_rel_path_to_json_scenes + m_currentScene.GetName() + m_scene_file_suffix, std::ios::trunc);
	if (!file.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to open " + m_rel_path_to_json_scenes + m_currentScene.GetName() + "\n, scene not saved";
		return;
	}
	file << std::setw(4) << *m_currentScene.GetData() << std::endl;
}

Scene* SceneManager::GetCurrentScene()
{
	if (m_currentScene.GetType() != SCENE_TYPE::FAULTY)
		return &m_currentScene;
	else
	{
		MessageWarning(SceneMgr_id) << "GetCurrentScene() returns nullptr!";
		return nullptr;
	}
}

const std::vector<std::string>& SceneManager::GetSceneNames()
{
	return m_sceneNames;
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
	nlohmann::json j;
	try { j = nlohmann::json::parse(data); }
	catch (const std::exception& exc)
	{
		std::string what(exc.what());
		MessageError(SceneMgr_id) << "Failed to parse scene names file to json object in _loadSceneNames(),\nexception message: " + what;
		return;
	}

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

}//namespace priv
}//namespace se