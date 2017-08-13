#include <gui/GraphicalUserInterface.h>
#include <core/Window.h>

#include <gui/EngineGui.h>
#include <gui/CompEditorGui.h>
#include <utility/EditorFunctions.h>
//
#include <gui/EngineGui.h>
#include <gui/GuiCompMgr.h>
#include <gui/GuiEntityMgr.h>
#include <gui/GuiSceneMgr.h>
#include <gui/ManagerGui.h>
//
#include <gui/CompEditorGui.h>
#include <gui/CCollidableEditor.h>
#include <gui/CDynamicEditor.h>
#include <gui/CShapeEditor.h>
#include <gui/CTextureEditor.h>
#include <gui/CAnimationEditor.h>
#include <gui/CTransformableEditor.h>

namespace se
{
namespace gui
{
std::map<COMPONENT_TYPE, gui::CompEditorGui*> GraphicalUserInterface::ComponentTypeToGuiEditor = {};

GraphicalUserInterface::GraphicalUserInterface(priv::Engine& engine_ref)
	: m_engine(engine_ref)
{

}

GraphicalUserInterface::~GraphicalUserInterface()
{
	//Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();
}

void GraphicalUserInterface::Initialize()
{
	//Set gui values
	window_data::width = m_engine.GetWindow().windowInitData.width;
	window_data::heigth = m_engine.GetWindow().windowInitData.heigth;

	//Initialize imgui IO. This file will hold users preference window positions and sizes. SE_TODO: Create switch for editor mode and deploy mode builds
	ImGui::GetIO().IniFilename = "engine_gui_conf.ini";

	//Init imgui using implementation provided in examples
	ImGui_ImplSdlGL3_Init(m_engine.GetWindow().GetWindowHandle());

	//SE_TODO: Let macro decide if these get build
	//Emplace manager classes' guis
	m_gui_container.emplace_back(std::make_unique<GuiSceneMgr>(m_engine, 1));
	m_gui_container.emplace_back(std::make_unique<GuiCompMgr>(m_engine, 3));		//Must be before GuiEntityMgr!!
	auto gui_compMgr = m_gui_container.back().get();
	m_gui_container.emplace_back(std::make_unique<gui::GuiEntityMgr>(m_engine, static_cast<se::gui::GuiCompMgr*>(gui_compMgr), 2));	//Must be after GuiCompMgr!!

	//Emplace component editors
	m_gui_container.emplace_back(std::make_unique<gui::CCollidableEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CDynamicEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CShapeEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CTextureEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CAnimationEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CTransformableEditor>(m_engine));


	//Sort elements according to their priority
	std::sort(m_gui_container.begin(), m_gui_container.end(), [&](const std::unique_ptr<EngineGui>& a, const std::unique_ptr<EngineGui>& b) {
		return a->GetUpdatePriotity() < b->GetUpdatePriotity();
	});
}

void GraphicalUserInterface::Update()
{

	//ImGui::SetNextWindowPos(ImVec2(se::gui::window_data::width / 2.0f, se::gui::window_data::heigth / 2.0f), ImGuiSetCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
	//ImGui::Begin("Engine");
	//ImGui::Text("SE Engine, %s");

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Debug settings"))
		{
			if (ImGui::BeginMenu("Draw settings"))
			{
				ImGui::Checkbox("Draw AABBs' lines", &gui::debug_draw_values::drawAABBs_lines);
				ImGui::Checkbox("Draw AABBs' points", &gui::debug_draw_values::drawAABBs_points);
				ImGui::Checkbox("Draw coll polys' lines", &gui::debug_draw_values::drawCollPolys_lines);
				ImGui::Checkbox("Draw coll polys' points", &gui::debug_draw_values::drawCollPolys_points);
				ImGui::Checkbox("Draw shapes' outline", &gui::debug_draw_values::drawShapes_lines);
				ImGui::Checkbox("Draw shapes' vertices", &gui::debug_draw_values::drawShapes_points);
				ImGui::Checkbox("Draw positions", &gui::debug_draw_values::drawPositions);;
				ImGui::Checkbox("Draw grid", &gui::debug_draw_values::drawGrid);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::Separator();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}
	//ImGui::End();


//SE_TODO: Create better gui structure
	for (auto& gui : m_gui_container)
	{
		gui->Update();
	}
}

}//namespace gui
}//namespace se