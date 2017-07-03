#include <core/Engine.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iomanip>
//#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>
#include <core/imgui_impl_sdl_gl3.h>


namespace se
{
namespace priv
{
//Static variables
ComponentDictionary Engine::componentDictionary{};
SystemForComponentDictionary Engine::systemForComponentDictionary{};


Engine::Engine()
	: j_config()
	, m_engine_clock()
	, m_frame_time()
	, m_input_coolDown()
	, m_window(new priv::Window)
	, m_movementSystem()
	, m_sceneMgr()
	, m_messenger()
{

}

Engine::~Engine()
{

}


void Engine::InitializeEngine()
{
	//Fetch engine settings from engine_config.json and apply them
	_initJConfigObject();
	_initAndApplyEngineSettings();

	//Initialize window and graphical context
	m_window->Initialize();

	///Init messenger
	m_messenger.Initialize();

	//Init imgui using implementation provided in examples
	ImGui_ImplSdlGL3_Init(m_window->GetWindowHandle());

	///Init managers
	m_sceneMgr.Initialize();

}

void Engine::UninitializeEngine()
{


}

void Engine::EngineUpdate()
{
	//Imgui test variables
	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImColor(114, 144, 154);



	bool loop = true;
	while (loop)
	{
		//
		m_frame_time = m_engine_clock.restart();
		float deltaTime = m_frame_time.asSeconds();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//Send events to ImGui_SDL_GL3_implentation
			ImGui_ImplSdlGL3_ProcessEvent(&event);

			if (event.type == SDL_QUIT)
				loop = false;

			if (event.type == SDL_KEYDOWN && m_input_coolDown.asMilliSeconds() < 100)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					loop = false;
					break;

				case SDLK_F12:
					//Switch if main window in editor is visible
					_gui_show_main_window = (_gui_show_main_window) ? false : true;
					break;

				default:
					break;
				}
			}


		}
		//New frame for imgui drawing
		ImGui_ImplSdlGL3_NewFrame(m_window->GetWindowHandle());


		///Update systems TODO: Thread these, mind the update order
		m_movementSystem.Update(deltaTime);



		//Engine window in editor //TODO: Move to own function
		if (_gui_show_main_window)
		{
			ImGui::SetWindowSize(ImVec2(500, 300), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Engine");
			ImGui::Text("SE Engine, %s");
			ImGui::Separator();
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("Scene manager"))
			{
				_gui_show_scene_mgr_window = (_gui_show_scene_mgr_window) ? false : true;
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		///Update managers
		m_sceneMgr.Update(_gui_show_scene_mgr_window);

		///Messenger should be last to update before render
		m_messenger.PrintMessages(_messageLogType_console);

		// Rendering
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		SDL_GL_SwapWindow(m_window->GetWindowHandle());
	}

	//Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();

}

void Engine::_initJConfigObject()
{
	//Read engine_config.json file and set engine settings accordingly
	std::ifstream data(REL_PATH_TO_ENGINE_CONFIG);
	if (data.is_open())
	{
		//Read data to single string
		j_config = nlohmann::json::parse(data);
		data.close();
	}
	else
	{
		MessageError(Engine_id) << "Failed to initialize json object in _initJConfigObject()";
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
	}

}

}//namespace priv
}//namespace se
