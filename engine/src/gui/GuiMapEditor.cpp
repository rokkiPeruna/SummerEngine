#include <gui/GuiMapEditor.h>
#include <core/Window.h>
#include <renderers/Camera.h>


namespace se
{
namespace gui
{
GuiMapEditor::GuiMapEditor(priv::Engine& engine_ref)
	: m_engine(engine_ref)
	, m_rel_filep_tilesheets(engine_ref.GetRelFilePathToUserFiles() + "resources/tilesheets/")
	, m_tilesheet_names{ engine_ref.GetResourceManager().GetTileSheetNames() }
	, m_curr_tilesheet_name{}
	, m_current_tilesheet{ nullptr }
	, m_tiles{}
	, m_curr_tiles_ind{ 0 }
	, m_current_tile{}
	, m_tile_number{ 0 }
	, m_tile_sz{ 0 }
	, m_sheet_sz{ 0 }
	, m_tex_screen_pos{ 0 }
	, m_show_sheet_window{ false }
{

}



void GuiMapEditor::Update()
{
	ImGui::BeginMainMenuBar();
	ImGui::SetCursorPosX(gui::window_data::width - 92);
	if (ImGui::Button("Close editor"))
		util::SwitchBoolean(elem_visibility::show_map_editor);

	SEbool show = true;
	ImGui::SetNextWindowSize(Vec2f(210.0f, 340.0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowPos(Vec2f(0.0f));
	ImGui::Begin("Tilesheets", &show, Vec2f(70.0f, 40.0f));
	for (auto sn : m_tilesheet_names)
	{
		if (ImGui::Button(sn.c_str()))
		{
			m_show_sheet_window = true;
			m_current_tilesheet = m_engine.GetResourceManager().LoadTileSheetResource(sn);
			m_curr_tilesheet_name = sn;
		}
	}
	//Handle tile adding to map
	if (!m_show_sheet_window && m_current_tile.tex_handle != SEuint_max && m_current_tilesheet)
		_handleTileAddingToScene();

	//Handle tile choosing
	if (m_show_sheet_window && m_current_tilesheet)
		_handleTileChoosing();

	_drawImageButtons(); ImGui::Separator();
	_showCurrSelectedTile();
	ImGui::End();
	ImGui::EndMainMenuBar();
}

/*FOR CHOOSING TILES*/
void GuiMapEditor::_handleTileChoosing()
{
	_tilePropEdit();
	_sheetPropEdit();

	//Set window
	ImGui::SetNextWindowSize(Vec2f(m_current_tilesheet->GetData().width, m_current_tilesheet->GetData().width), ImGuiSetCond_Appearing);
	ImGui::SetNextWindowPos(Vec2f(gui::window_data::width / 2.0f - m_current_tilesheet->GetData().width / 2.0f, gui::window_data::heigth / 2.0f - m_current_tilesheet->GetData().heigth / 2.0f));
	ImGui::Begin(m_curr_tilesheet_name.c_str(), &m_show_sheet_window);
	//Cursor screen position
	m_tex_screen_pos = ImGui::GetCursorScreenPos();

	ImGui::Image(
		(void*)static_cast<SEuint64>(m_current_tilesheet->GetData().handle),
		ImVec2(static_cast<SEfloat>(m_current_tilesheet->GetData().width), static_cast<SEfloat>(m_current_tilesheet->GetData().heigth)));

	//If mouse is hovered, calculate current tile number
	if (ImGui::IsItemHovered() && m_tile_sz.x > 0 && m_tile_sz.y > 0)
	{
		Vec2i tile_coords = _calcTilesXYcoords();
		ImGui::BeginTooltip();
		ImGui::Text("Tile num: (%2d, %2d)", tile_coords.x, tile_coords.y);
		ImGui::EndTooltip();

		if (ImGui::IsMouseClicked(0))
			_createAndAddTile(tile_coords.x, tile_coords.y);
	}
	ImGui::End();
}

void GuiMapEditor::_tilePropEdit()
{
	ImGui::SliderInt("Tile width", &m_current_tilesheet->GetData().tile_width, 1, 512);
	ImGui::SliderInt("Tile heigth", &m_current_tilesheet->GetData().tile_heigth, 1, 512);
	m_tile_sz = Vec2u{ m_current_tilesheet->GetData().tile_width, m_current_tilesheet->GetData().tile_heigth };
}

void GuiMapEditor::_sheetPropEdit()
{
	m_sheet_sz = Vec2u{ m_current_tilesheet->GetData().width, m_current_tilesheet->GetData().heigth };
}

void GuiMapEditor::_createAndAddTile(SEint tile_x_coord, SEint tile_y_coord)
{
	priv::Tile td;
	td.tex_handle = m_current_tilesheet->GetData().handle;
	td.x = (m_tile_sz.x * tile_x_coord) - (m_tile_sz.x);
	td.y = (m_tile_sz.y * tile_y_coord) - (m_tile_sz.y);
	td.w = m_tile_sz.x;
	td.h = m_tile_sz.y;
	td.pw = m_current_tilesheet->GetData().width;
	td.ph = m_current_tilesheet->GetData().heigth;

	//Calculate normalized tex coords
	SEfloat norm_x = td.x / static_cast<SEfloat>(td.pw);
	SEfloat norm_y = td.y / static_cast<SEfloat>(td.ph);
	SEfloat norm_w = td.w / static_cast<SEfloat>(td.pw);
	SEfloat norm_h = td.h / static_cast<SEfloat>(td.ph);
	td.norm_tex_coords = Vec4f(norm_x, norm_y, norm_x + norm_w, norm_y + norm_h);

	if (m_curr_tiles_ind < internal_NUM_TILES)
		m_tiles[m_curr_tiles_ind++] = td;
}

Vec2i GuiMapEditor::_calcTilesXYcoords()
{
	//Mouse position relative to texture
	SEint uv_x = static_cast<SEint>(ImGui::GetMousePos().x - m_tex_screen_pos.x);
	SEint uv_y = static_cast<SEint>(ImGui::GetMousePos().y - m_tex_screen_pos.y);
	//Tile that mouse points to
	SEint x = ((SEfloat)uv_x) / ((SEfloat)m_current_tilesheet->GetData().tile_width) + 1;
	SEint y = ((SEfloat)uv_y) / ((SEfloat)m_current_tilesheet->GetData().tile_heigth) + 1;

	return Vec2f(x, y);
}

void GuiMapEditor::_drawImageButtons()
{
	SEint same_line_counter = 0;
	for (SEint i = 0; i < m_curr_tiles_ind; ++i, ++same_line_counter)
	{
		ImGui::PushID(i);
		if (ImGui::ImageButton(
			(void*)static_cast<SEuint64>(m_tiles[i].tex_handle),
			ImVec2(static_cast<SEfloat>(m_tiles[i].w), static_cast<SEfloat>(m_tiles[i].h)),
			ImVec2(m_tiles[i].norm_tex_coords.x, m_tiles[i].norm_tex_coords.y),
			ImVec2(m_tiles[i].norm_tex_coords.z, m_tiles[i].norm_tex_coords.w),
			0
		))
		{
			m_current_tile = m_tiles[i];
		}
		ImGui::PopID();

		if (same_line_counter == 4)
			same_line_counter = 0;
		else
			ImGui::SameLine();
	}
}

void GuiMapEditor::_showCurrSelectedTile()
{
	if (m_current_tile.tex_handle != SEuint_max)
	{
		ImGui::Text("Current tile:");
		ImGui::Image(
			(void*)static_cast<SEuint64>(m_current_tile.tex_handle),
			ImVec2(static_cast<SEfloat>(m_current_tile.w), static_cast<SEfloat>(m_current_tile.h)),
			ImVec2(m_current_tile.norm_tex_coords.x, m_current_tile.norm_tex_coords.y),
			ImVec2(m_current_tile.norm_tex_coords.z, m_current_tile.norm_tex_coords.w)
		);
	}
}


/*FOR ADDING TILE TO SCENE*/
void GuiMapEditor::_handleTileAddingToScene()
{
	if (ImGui::IsMouseClicked(0))
	{
		priv::Tile t = m_current_tile;
		Vec2f mousepos = ImGui::GetMousePos();
		Vec2i norm_pos = util::ScreenCoordsToNormOpenGLCoords(mousepos.x, mousepos.y, Vec2i(gui::window_data::width, gui::window_data::heigth), m_engine.GetCamera()->GetPosition());
		t.position = Vec2f(std::round(norm_pos.x), std::round(norm_pos.y));
		m_engine.GetMapCreator().AddTileToMap(t);

		std::string m = std::to_string(mousepos.x) + "  " + std::to_string(mousepos.y);
		std::string p = std::to_string(t.x) + "  " + std::to_string(t.y);
		MessageWarning(_nullSysMgr_id) << "Tile pos: " + p;
		MessageWarning(_nullSysMgr_id) << "mouse pos: " + m;
	}
}

}//namespace gui
}//namespace se