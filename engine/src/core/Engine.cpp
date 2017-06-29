#include <core/Engine.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <nlohmann_json/json.hpp>
#include <imgui/imgui.h>
#include <core/imgui_impl_sdl_gl3.h>

//Include GUI implementations


namespace se
{
namespace priv
{
//Static variables
ComponentDictionary Engine::componentDictionary{};
SystemForComponentDictionary Engine::systemForComponentDictionary{};


Engine::Engine()
	: m_engine_clock()
	, m_frame_time()
	, m_window(new priv::Window)
	, m_graphics(new priv::Graphics)
	, m_movementSystem()
	, m_entityCompMgr()
{

}

Engine::~Engine()
{

}


void Engine::InitializeEngine()
{
	//Read engine_config.json file and set engine settings accordingly
	nlohmann::json j_eng_conf;
	//std::ifstream data("engine_config.json", std::ios::out);
	std::ifstream data("../../engine/json_files/engine_config.json");
	if (data.is_open())
	{
		//Read data to single string
		j_eng_conf = nlohmann::json::parse(data);
	}
	else
	{
		//TODO: send message
	}

	//Send window size data to Window
	if (j_eng_conf.find("window_width") != j_eng_conf.end())
	{
		m_window->windowWidth = j_eng_conf.at("window_width");
	}
	if (j_eng_conf.find("window_heigth") != j_eng_conf.end())
	{
		m_window->windowHeigth = j_eng_conf.at("window_heigth");
	}

	m_window->InitializeWindow();
	m_graphics->InitializeGraphics(m_window);

	//Init imgui using imolementation provided in examples
	ImGui_ImplSdlGL3_Init(m_window->GetWindowHandle());

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

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					loop = false;
					break;

				case SDLK_r:
					// Cover with red and update
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(m_window->GetWindowHandle());
					break;

					//	case SDLK_g:
					//		// Cover with green and update
					//		glClearColor(0.0, 1.0, 0.0, 1.0);
					//		glClear(GL_COLOR_BUFFER_BIT);
					//		SDL_GL_SwapWindow(m_window->GetWindowHandle());
					//		break;

					//	case SDLK_b:
					//		// Cover with blue and update
					//		glClearColor(0.0, 0.0, 1.0, 1.0);
					//		glClear(GL_COLOR_BUFFER_BIT);
					//		SDL_GL_SwapWindow(m_window->GetWindowHandle());
					//		break;

					//	case SDL_FINGERDOWN:

					//		glClearColor(1.0, 1.0, 0.0, 1.0);
					//		glClear(GL_COLOR_BUFFER_BIT);
					//		SDL_GL_SwapWindow(m_window->GetWindowHandle());
					//		break;

					//	case SDL_FINGERUP:

					//		glClearColor(0.0, 1.0, 1.0, 1.0);
					//		glClear(GL_COLOR_BUFFER_BIT);
					//		SDL_GL_SwapWindow(m_window->GetWindowHandle());
					//		break;

					//	case SDL_FINGERMOTION:

					//		glClearColor(1.0, 0.0, 1.0, 1.0);
					//		glClear(GL_COLOR_BUFFER_BIT);
					//		SDL_GL_SwapWindow(m_window->GetWindowHandle());
					//		break;

				default:
					break;
				}
			}


		}
		//New frame for imgui drawing
		ImGui_ImplSdlGL3_NewFrame(m_window->GetWindowHandle());
		m_movementSystem.Update(deltaTime);
		//gui::UpdateMovementSystemGUI();

		// 1. Show a simple window
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		{
			ImGui::Begin("Editor");
			static float f = 0.0f;
			ImGui::Text("Create entity");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("Entity editor")) show_test_window ^= 1;
			if (ImGui::Button("Scene editor")) show_another_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

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
}//namespace priv
}//namespace se
