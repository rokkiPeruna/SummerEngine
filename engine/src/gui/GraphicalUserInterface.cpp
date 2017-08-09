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
	//Initialize imgui IO. This file will hold users preference window positions and sizes. SE_TODO: Create switch for editor mode and deploy mode builds
	ImGui::GetIO().IniFilename = "engine_gui_conf.ini";


	//Init imgui using implementation provided in examples
	ImGui_ImplSdlGL3_Init(m_engine.GetWindow().GetWindowHandle());

	//SE_TODO: Let macro decide if these get build
	//Emplace manager classes' guis
	m_gui_container.emplace_back(std::make_unique<GuiSceneMgr>(m_engine));
	m_gui_container.emplace_back(std::make_unique<GuiCompMgr>(m_engine));		//Must be before GuiEntityMgr!!
	auto gui_compMgr = m_gui_container.back().get();
	m_gui_container.emplace_back(std::make_unique<gui::GuiEntityMgr>(m_engine, static_cast<se::gui::GuiCompMgr*>(gui_compMgr)));	//Must be after GuiCompMgr!!

	//Emplace component editors
	m_gui_container.emplace_back(std::make_unique<gui::CCollidableEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CDynamicEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CShapeEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CTextureEditor>(m_engine));
	m_gui_container.emplace_back(std::make_unique<gui::CTransformableEditor>(m_engine));
}

void GraphicalUserInterface::Update()
{
	//Engine window in editor
	if (se::gui::show_main_window)
	{
		ImGui::SetNextWindowPos(ImVec2(se::gui::win_width / 2, se::gui::win_heigth / 2), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(100.f, 100.f), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Engine");
		ImGui::Text("SE Engine, %s");

		if (ImGui::Button("Draw AABBs' lines"))
			util::SwitchBoolean(gui::debug_draw_values::drawAABBs_lines);
		ImGui::SameLine();
		if (ImGui::Button("Draw AABBs' points"))
			util::SwitchBoolean(gui::debug_draw_values::drawAABBs_points);

		if (ImGui::Button("Draw coll polys' lines"))
			util::SwitchBoolean(gui::debug_draw_values::drawCollPolys_lines);
		ImGui::SameLine();
		if (ImGui::Button("Draw coll polys' points"))
			util::SwitchBoolean(gui::debug_draw_values::drawCollPolys_points);

		if (ImGui::Button("Draw shapes' outline"))
			util::SwitchBoolean(gui::debug_draw_values::drawShapes_lines);
		ImGui::SameLine();
		if (ImGui::Button("Draw shapes' vertices"))
			util::SwitchBoolean(gui::debug_draw_values::drawShapes_points);

		if (ImGui::Button("Draw positions"))
			util::SwitchBoolean(gui::debug_draw_values::drawPositions);

		ImGui::Separator();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	//SE_TODO: Create better gui structure
	for (auto& gui : m_gui_container)
	{
		gui->Update();
	}
}

}//namespace gui
}//namespace se