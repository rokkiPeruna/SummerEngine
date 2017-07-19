#include <core/Engine.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <exception>
//#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>
#include <core/imgui_impl_sdl_gl3.h>


namespace se
{
namespace priv
{
std::map<COMPONENT_TYPE, ComponentSystem*> Engine::ComponentTypeToSystemPtr = {};

Engine::Engine()
	: m_eng_conf_file_name("engine_config.json")
	, m_current_project_name("")
	, m_json_data_files_fold_name("data")
	, m_path_to_user_files("")
	, j_config()
	, m_inEditorLoop(false)
	, m_engine_clock()
	, m_frame_time()
	, m_input_coolDown()
	, m_window(new priv::Window)
	, m_movementSystem()
	, m_entityMgr()
	, m_sceneMgr()
	, m_resourceMgr()
	, m_renderMgr()
	, m_compMgr()
	, m_messenger()
	, m_renderSystem()
	
{

}

Engine::~Engine()
{

}


void Engine::Initialize(const std::string& projectName)
{
	//Set to start at editor loop //SE_TODO: Create switch(macro, etc.) to decide loop mode
	m_inEditorLoop = true;

	m_current_project_name = projectName;
	//Create path from .vcproj or .exe to the json files containing game data.
	_findPathToUserFiles();

	//Read engine settings to json object for later use
	if (_initJConfigObject())
	{
		_initAndApplyEngineSettings();
	}
	else
	{
		std::runtime_error("Failed to initialize json object in Engine::Initialize()");
		return;
	}
	
	m_window->Initialize();

	m_messenger.Initialize();

	_initManagers();
	_initSystems();

	//Init imgui using implementation provided in examples
	ImGui_ImplSdlGL3_Init(m_window->GetWindowHandle());
}

void Engine::Uninitialize()
{


}

void Engine::EngineUpdate()
{
	bool exitProgram = false;
	while (!exitProgram)
	{
		if (!m_inEditorLoop)
			m_inEditorLoop = _gameLoop();
		else
			_editorLoop(exitProgram);
	}

	//Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();

}

bool Engine::_initJConfigObject()
{
	//Read engine_config.json file and set engine settings accordingly
	std::ifstream data(m_path_to_user_files + m_eng_conf_file_name);
	if (data.is_open())
	{
		//Read data to single string
		j_config = nlohmann::json::parse(data);
		data.close();
		return true;
	}
	else
	{
		MessageError(Engine_id) << "Failed to initialize json object in _initJConfigObject()";
		return false;
	}
}

void Engine::_findPathToUserFiles()
{
	//Find out where user files are located:
	std::ifstream deploypath(m_json_data_files_fold_name);
	if (deploypath.is_open())
	{
		m_path_to_user_files = m_json_data_files_fold_name + "/";
		deploypath.close();
		return;
	}
	else
	{
		m_path_to_user_files = "../../projects/" + m_current_project_name + "/" + m_json_data_files_fold_name + "/";
	}


}

void Engine::_initAndApplyEngineSettings()
{
	MessageInfo(Engine_id) << "Applying window settings..";
	//Initialize window settings
	auto& winset_json = j_config.find("window_settings");
	if (winset_json != j_config.end())
	{
		auto& stngs = winset_json.value();
		auto& windata = m_window->windowInitData;
		//Send window size data to Window
		if (stngs.find("window_name") != stngs.end())
			windata.name = stngs.at("window_name");
		if (stngs.find("window_width") != stngs.end())
			windata.width = stngs.at("window_width");
		if (stngs.find("window_heigth") != stngs.end())
			windata.heigth = stngs.at("window_heigth");
		if (stngs.find("window_pos_x") != stngs.end())
			windata.pos_x = stngs.at("window_pos_x");
		if (stngs.find("window_pos_y") != stngs.end())
			windata.pos_y = stngs.at("window_pos_y");
		if (stngs.find("window_centered") != stngs.end())
			windata.centered = stngs.at("window_centered");
		if (stngs.find("window_fullscreen") != stngs.end() && stngs.at("window_fullscreen") != 0)
			windata.sdl_settings_mask += SDL_WINDOW_FULLSCREEN;
		if (stngs.find("window_borderless") != stngs.end() && stngs.at("window_borderless") != 0)
			windata.sdl_settings_mask += SDL_WINDOW_BORDERLESS;

		//Set window size to global values for GUI
		_gui_width = windata.width;
		_gui_heigth = windata.heigth;
	}

	//Initialize imgui IO. This file will hold users preference window positions and sizes. SE_TODO: Create switch for editor mode and deploy mode builds
	ImGui::GetIO().IniFilename = "engine_gui_conf.ini";

}

void Engine::_initManagers()
{
	//SceneMgr
	m_sceneMgr.Initialize(m_path_to_user_files, &m_entityMgr);

	//EntityManager
	m_entityMgr.Initialize(m_path_to_user_files, &m_compMgr);

	//ComponentManager
	m_compMgr.Initialize(m_path_to_user_files);

	//Resource Manager | default path to shaders.. todo: change so that it can be read fomr the engine_config.json or delete that part from json
	m_resourceMgr.Initialize("../../engine/shaders/");

	
//	m_renderMgr.Initialize();
}

void Engine::_initSystems()
{
	m_movementSystem.Initialize();
	m_systemContainer.emplace_back(&m_movementSystem);
	m_transformSystem.Initialize();
	m_systemContainer.emplace_back(&m_transformSystem);
	m_renderSystem.Initialize();
	m_systemContainer.emplace_back(&m_renderSystem);
}

void Engine::_updateMgrs()
{
	m_sceneMgr.Update();
	m_entityMgr.Update();
}

void Engine::_updateSystems(SEfloat deltaTime)
{
	m_movementSystem.Update(deltaTime);
}

void Engine::_updateGUI()
{
	//Engine window in editor
	if (_gui_show_main_window)
	{
		ImGui::SetNextWindowPos(ImVec2(_gui_width / 2, _gui_heigth / 2), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Engine");
		ImGui::Text("SE Engine, %s");
		ImGui::Separator();
		if (ImGui::Button("Scenes"))
			_gui_show_scene_mgr_window = (_gui_show_scene_mgr_window) ? false : true;

		if (ImGui::Button("EntCompMgr"))
			_gui_show_entity_comp_mgr_window = (_gui_show_entity_comp_mgr_window) ? false : true;

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	//SE_TODO: Create better gui structure
	m_entityMgr.ShowAndUpdateGUI();
	m_sceneMgr.ShowAndUpdateGUI();
	m_compMgr.ShowAndUpdateGUI();

}

bool Engine::_gameLoop()
{
	ImVec4 clear_color = ImColor(114, 144, 154);

	SDL_Event event;
	bool gameloop = true;
	m_engine_clock.restart();
	while (gameloop)
	{
		m_frame_time = m_engine_clock.restart();
		SEfloat deltaTime = m_frame_time.asSeconds();

		while (SDL_PollEvent(&event))
		{

			if (event.type == SDL_QUIT)
				gameloop = false;

			if (event.type == SDL_KEYDOWN && m_input_coolDown.asMilliSeconds() < 100)
			{
				switch (event.key.keysym.sym)
				{
				case Key_Escape:
					gameloop = false;
					break;
				case Key_F11:
					m_inEditorLoop = true;
				case Key_F12:
					//Switch if main window in editor is visible
					_gui_show_main_window = (_gui_show_main_window) ? false : true;
					break;
				default:
					break;
				}
			}
		}
		_updateMgrs();

		_updateSystems(deltaTime);

		//Messenger should be last to update before render
		//m_messenger.PrintMessages(_messageLogType_console);

		// Rendering
		glViewport(0, 0, _gui_width, _gui_heigth);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(m_window->GetWindowHandle());
	}
	return true;
}

void Engine::_editorLoop(SEbool& exitProgram)
{
	ImVec4 clear_color = ImColor(114, 144, 154);

	m_frame_time = m_engine_clock.restart();
	SEfloat deltaTime = m_frame_time.asSeconds();
	SDL_Event event;
	bool editorloop = true;
	while (editorloop)
	{
		while (SDL_PollEvent(&event))
		{
			
		
			//Send events to ImGui_SDL_GL3_implentation //SE_TODO: Switch by macro, bool, etc.
			ImGui_ImplSdlGL3_ProcessEvent(&event);

			if (event.type == SDL_QUIT)
				editorloop = false;

			if (event.type == SDL_KEYDOWN && m_input_coolDown.asMilliSeconds() < 100)
			{
				switch (event.key.keysym.sym)
				{
				case Key_Escape:
					editorloop = false; exitProgram = true;
					break;
				case Key_F11:
					editorloop = false; m_inEditorLoop = false;
					break;
				case Key_F12:
					//Switch if main window in editor is visible
					_gui_show_main_window = (_gui_show_main_window) ? false : true;
					break;

				default:
					break;
				}
			}


		}
		//New frame for imgui drawing //SE_TODO: Switch by macro, bool, etc.
		ImGui_ImplSdlGL3_NewFrame(m_window->GetWindowHandle());
		_updateGUI(); //SE_TODO: Switch by macro, bool, etc.
		_updateMgrs();

		//Messenger should be last to update before render
		m_messenger.PrintMessages(_messageLogType_console);

		// Rendering
		glViewport(0, 0, _gui_width, _gui_heigth);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		
	//	m_renderMgr.UpdateRenderManager(m_window->GetWindowHandle(), m_resourceMgr.GetShaderProgram("testShader"));
		m_renderSystem.Update(deltaTime);

		ImGui::Render();
		SDL_GL_SwapWindow(m_window->GetWindowHandle());
	}
}

}//namespace priv
}//namespace se
