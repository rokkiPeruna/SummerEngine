#include <managers/SceneManager.h>
#include <systems/ComponentSystem.h>
#include <utility/JsonUtilFunctions.h>

namespace se
{
namespace priv
{
SceneManager::SceneManager(Engine& engine_ref)
	: Manager(engine_ref)
	, m_sceneJsonObject()
	, m_sceneNamesJsonObject()
	, m_rel_path_to_json_scenes("")
	, m_currentScene("", SCENE_TYPE::FAULTY, 0, 0)
	, m_sceneNames{}
	, ffd()
	, sf_struct()
	, snaf_struct()
{

}

void SceneManager::Initialize(const std::string& filepathToUserFiles, EntityManager* entityMgr_ptr, ComponentManager* compMgr_ptr)
{
	///Register event handler
	m_engine.GetEventManager().RegisterEventHandler(m_event_handler);
	///Register desired events
	assert(m_event_handler);
	//m_event_handler->RegisterEvent()

	///Relative path to scenes.json file
	m_rel_path_to_json_scenes = filepathToUserFiles + ffd.scene_folder_name;

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
	std::ofstream newScene(m_rel_path_to_json_scenes + scenename + ffd.scene_file_suffix);
	if (!newScene.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to create new scene file[" + scenename + "],\nin AddScene, scene not added, returning";
		return false;
	}
	_createStructToNewScene(newScene, scenename, type, width, heigth);
	newScene.close();

	//Rewrite m_scene_name_list_file
	m_sceneNamesJsonObject.clear(); //SE_TODO: Is there need to rewrite the object??
	try { util::ReadFileToJson(m_sceneNamesJsonObject, m_rel_path_to_json_scenes + ffd.scene_names_file_name, SceneMgr_id); }
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


	auto& names_obj = m_sceneNamesJsonObject.find(snaf_struct.scenenamelist_obj_name);

	if (names_obj == m_sceneNamesJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object" + snaf_struct.scenenamelist_obj_name + ",\n, scene name not added to " +
			snaf_struct.scenenamelist_obj_name + ", removing scene file, scene not added";
		std::remove((m_rel_path_to_json_scenes + scenename + ffd.scene_file_suffix).c_str());
		return false;
	}
	names_obj.value().push_back(scenename);

	util::RewriteFileWithJson(m_sceneNamesJsonObject, m_rel_path_to_json_scenes + snaf_struct.scenenamelist_obj_name, SceneMgr_id);

	//Add name to runtime container
	m_sceneNames.emplace_back(scenename);

	return true;
}

void SceneManager::SaveScene(std::string, SCENE_TYPE, SEint, SEint)
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

	//Delete current renderer's render batches
	m_engine.GetCurrentRenderer()->ClearRenderBatches();

	try { util::ReadFileToJson(m_sceneJsonObject, m_rel_path_to_json_scenes + scenename + ffd.scene_file_suffix, SceneMgr_id); }
	catch (const se_exception& exc)
	{
		MessageError(SceneMgr_id) << "Failed to parse [" + scenename + "] json object or failed to open\nfile " + m_rel_path_to_json_scenes + scenename + ffd.scene_file_suffix
			+ ",\nexception message: " + exc.msg;
		return false;
	}

	//Read scene's info to json object and create new current scene
	auto& info_obj = m_sceneJsonObject.find(sf_struct.info_obj_name);
	if (info_obj == m_sceneJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object " + snaf_struct.scenenamelist_obj_name + "\nin LoadScene, scene not loaded!";
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
	//Check that main object is valid
	auto& main_obj = m_sceneJsonObject.find(sf_struct.prim_obj_name);
	if (main_obj == m_sceneJsonObject.end())
	{
		MessageError(SceneMgr_id) << "Could not find " + sf_struct.prim_obj_name + " in " + scenename + ffd.scene_file_suffix + "\n, scene not loaded!";
		return false;
	}
	//And if it is, give it to m_currentScene, empty systems component containers and init new scene
	m_currentScene.SetData(&m_sceneJsonObject);

	for (auto& s : m_engine.GetSystemsContainer())
	{
		s->ClearComponentContainers();
	}

	m_event_handler->SendEvent(SE_Event_SceneChanged(&m_currentScene));
	return true;
}

void SceneManager::ReinitScene()
{
	if (m_currentScene.GetType() != SCENE_TYPE::FAULTY)
	{
		LoadScene(m_currentScene.GetName(), true);
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

	std::ofstream file(m_rel_path_to_json_scenes + m_currentScene.GetName() + ffd.scene_file_suffix, std::ios::trunc);
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
	return nullptr;
}

const std::vector<std::string>& SceneManager::GetSceneNames()
{
	return m_sceneNames;
}

void SceneManager::_loadSceneNames()
{
	std::ifstream data(m_rel_path_to_json_scenes + ffd.scene_names_file_name);
	if (!data.is_open())
	{
		MessageError(SceneMgr_id) << "Failed to open " + m_rel_path_to_json_scenes + ffd.scene_names_file_name + "\n for reading, no scenes loaded, returning";
		return;
	}
	//Check if m_scene_name_list_file is empty //SE_TODO: Better way to check emptiness exists
	if (data.peek() == std::ifstream::traits_type::eof())
	{
		MessageInfo(SceneMgr_id) << ffd.scene_names_file_name + " is empty, no basic json structure available, creating json structure";
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

	auto& names_obj = j.find(snaf_struct.scenenamelist_obj_name);
	if (names_obj == j.end())
	{
		MessageError(SceneMgr_id) << "Failed to open json object " + snaf_struct.scenenamelist_obj_name + " in " + ffd.scene_names_file_name + ",\nscenes not loaded";
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
		"\"" + sf_struct.info_obj_name + "\":{\n" <<
		"\t\"name\":\"" + scenename + "\",\n" <<
		"\t\"type\":" + typestr + ",\n" <<
		"\t\"width\":" + w + ",\n" <<
		"\t\"heigth\":" + h + "\n" <<
		"},\n"
		"\"" + sf_struct.prim_obj_name + "\":{\n" <<
		"  }\n" <<
		"}" << std::endl;
}

void SceneManager::_createStructToScnNamesJson()
{
	std::ofstream data(m_rel_path_to_json_scenes + ffd.scene_names_file_name);
	if (!data.is_open())
	{
		MessageWarning(SceneMgr_id) << "Failed to open " + ffd.scene_names_file_name + " in _createStructToScnNamesJson()";
		return;
	}
	//
	data << "{\n" <<
		"\"" + snaf_struct.scenenamelist_obj_name + "\":[\n" <<
		"  ]\n" <<
		"}" << std::endl;
	data.close();
}

}//namespace priv
}//namespace se