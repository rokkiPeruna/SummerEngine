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
#include <gui/CGameLogicEditor.h>
//
#include <gui/GuiMapEditor.h>

namespace se
{
namespace gui
{
std::map<COMPONENT_TYPE, gui::CompEditorGui*> GraphicalUserInterface::ComponentTypeToGuiEditor = {};

GraphicalUserInterface::GraphicalUserInterface(priv::Engine& engine_ref)
	: m_engine(engine_ref)
	, m_event_handler{nullptr}
	, m_gui_container{}
	, m_map_editor{nullptr}
	
{

}

GraphicalUserInterface::~GraphicalUserInterface()
{
	//Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();
}

void GraphicalUserInterface::Initialize()
{
	//Event handler
	m_engine.GetEventManager().RegisterEventHandler(m_event_handler);
	assert(m_event_handler);

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
	m_gui_container.emplace_back(std::make_unique<gui::CGameLogicEditor>(m_engine));

	//Sort elements according to their priority
	std::sort(m_gui_container.begin(), m_gui_container.end(), [&](const std::unique_ptr<EngineGui>& a, const std::unique_ptr<EngineGui>& b) {
		return a->GetUpdatePriotity() < b->GetUpdatePriotity();
	});

	m_map_editor = std::make_unique<GuiMapEditor>(m_engine);
}

void GraphicalUserInterface::Update()
{

	if (elem_visibility::show_map_editor)
		m_map_editor->Update();

	else
	{
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

			if (ImGui::Button("Map editor"))
				util::SwitchBoolean(gui::elem_visibility::show_map_editor);
			ImGui::SameLine();
			if (ImGui::Button("Save progress"))
				m_event_handler->SendEvent(SE_Cmd_SaveScene());

			ImGui::EndMainMenuBar();
		}
		//ImGui::End();



		for (auto& gui : m_gui_container)
		{
			gui->Update();
		}
	}
}

}//namespace gui
}//namespace se