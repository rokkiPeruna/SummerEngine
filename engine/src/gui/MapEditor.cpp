#include <gui/MapEditor.h>
#include <core/Window.h>
#include <managers/ResourceManager.h>

namespace se
{
namespace gui
{

MapEditor::MapEditor(priv::Engine& engine_ref)
	: m_engine(engine_ref)
	, m_rel_filep_tilesheets(engine_ref.GetRelFilePathToUserFiles() + "resources/tilesheets/")
	, m_tilesheet_names{ engine_ref.GetResourceManager().GetTileSheetNames() }
{

}


void MapEditor::Update()
{


	//ImGui::SetNextWindowSize(ImVec2(window_data::width, window_data::heigth), ImGuiSetCond_Always);
	//ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::BeginMainMenuBar();
	if (ImGui::Button("Close editor"))
		util::SwitchBoolean(elem_visibility::show_map_editor);

	{
		SEbool show = true;
		ImGui::Begin("Tilesheets", &show, Vec2f(70.0f, 100.0f));
		for (auto sn : m_tilesheet_names)
		{
			if (ImGui::Button(sn.c_str()))
			{
				m_engine.GetResourceManager().LoadTileSheetResource(sn);
			}
		}
		ImGui::End();
	}

	ImGui::EndMainMenuBar();

}

}//namespace gui
}//namespace se