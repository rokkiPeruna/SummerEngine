#include <gui/GuiMapEditor.h>
#include <core/Window.h>


namespace se
{
namespace gui
{

GuiMapEditor::GuiMapEditor(priv::Engine& engine_ref)
	: m_engine(engine_ref)
	, m_rel_filep_tilesheets(engine_ref.GetRelFilePathToUserFiles() + "resources/tilesheets/")
	, m_tilesheet_names{ engine_ref.GetResourceManager().GetTileSheetNames() }
	, m_current_tilesheet{nullptr}
{

}

namespace
{
SEbool show = true;
static Vec2u tile_number{ 0 };
static Vec2u tile_sz{ 0 };
static Vec2u sheet_sz{ 0 };
}

void GuiMapEditor::Update()
{
	static SEbool show_sheet_window = false;

	//ImGui::SetNextWindowSize(ImVec2(window_data::width, window_data::heigth), ImGuiSetCond_Always);
	//ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::BeginMainMenuBar();
	if (ImGui::Button("Close editor"))
		util::SwitchBoolean(elem_visibility::show_map_editor);

	{
		//static SEint slider_w{ 0 };

		ImGui::Begin("Tilesheets", &show, Vec2f(70.0f, 100.0f));
		for (auto sn : m_tilesheet_names)
		{
			if (ImGui::Button(sn.c_str()))
			{
				show_sheet_window = true;
				//Load tile sheet
				m_current_tilesheet = m_engine.GetResourceManager().LoadTileSheetResource(sn);
			}

			if (show_sheet_window && m_current_tilesheet)
			{

				//Tile size
				ImGui::SliderInt("Tile width", &m_current_tilesheet->GetData().tile_width, 1, 512);

				ImGui::SliderInt("Tile heigth", &m_current_tilesheet->GetData().tile_heigth, 1, 512);

				//Set window
				ImGui::SetNextWindowSize(Vec2f(m_current_tilesheet->GetData().width, m_current_tilesheet->GetData().width), ImGuiSetCond_Appearing);
				ImGui::SetNextWindowPos(Vec2f(gui::window_data::width / 2.0f - m_current_tilesheet->GetData().width / 2.0f, gui::window_data::heigth / 2.0f - m_current_tilesheet->GetData().heigth / 2.0f));
				ImGui::Begin("Sheet", &show_sheet_window);

				//Cursor screen position
				ImVec2 tex_screen_pos = ImGui::GetCursorScreenPos();

				//Tile size
				tile_sz = Vec2u{ m_current_tilesheet->GetData().tile_width, m_current_tilesheet->GetData().tile_heigth };

				//Sheet size
				sheet_sz = Vec2u{ m_current_tilesheet->GetData().width, m_current_tilesheet->GetData().heigth };

				//Add image
				ImGui::GetWindowDrawList()->AddImage(
					(void*)static_cast<SEuint64>(m_current_tilesheet->GetData().handle),
					Vec2f(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y),
					Vec2f(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y)
				);
				ImGui::Image(
					(void*)static_cast<SEuint64>(m_current_tilesheet->GetData().handle),
					ImVec2(static_cast<SEfloat>(m_current_tilesheet->GetData().width), static_cast<SEfloat>(m_current_tilesheet->GetData().heigth)));

				//If mouse is hovered, calculate current tile number
				if (ImGui::IsItemHovered())
				{
					//Mouse position relative to texture
					SEint uv_x = static_cast<SEint>(ImGui::GetMousePos().x - tex_screen_pos.x);
					SEint uv_y = static_cast<SEint>(ImGui::GetMousePos().y - tex_screen_pos.y);

					if (tile_sz.x > 0 && tile_sz.y > 0)
					{

						SEint x = ((SEfloat)uv_x) / ((SEfloat)m_current_tilesheet->GetData().tile_width);
						SEint y = ((SEfloat)uv_y) / ((SEfloat)m_current_tilesheet->GetData().tile_heigth); +++


						ImGui::BeginTooltip();
						ImGui::Text("UV coords: (%.2f, %.2f)", uv_x, uv_y);
						ImGui::Text("Tile num: (%.0f, %.0f)", x, y);
						ImGui::EndTooltip();


						if (ImGui::IsMouseClicked(0))
						{

						}
					}
				}
				ImGui::End();
			}
		}
		ImGui::End();
	}

	ImGui::EndMainMenuBar();

}

}//namespace gui
}//namespace se