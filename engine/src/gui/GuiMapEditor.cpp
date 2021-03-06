#include <gui/GuiMapEditor.h>
#include <core/Window.h>
#include <renderers/Camera.h>


namespace se
{
namespace gui
{
GuiMapEditor::GuiMapEditor(priv::Engine& engine_ref)
	: m_engine(engine_ref)
	, m_map_creator{ engine_ref.GetMapCreator() }
	, mouse{}
	, m_rel_filep_tilesheets(engine_ref.GetRelFilePathToUserFiles() + "resources/tilesheets/")
	, m_tilesheet_names{ engine_ref.GetResourceManager().GetTileSheetNames() }
	, m_curr_tilesheet_name{}
	, m_current_tilesheet{ nullptr }
	, m_tiles{}
	, m_curr_tiles_ind{ 0 }
	, m_current_tile{}
	, ppu{ m_engine.GetPixelsPerOneUnit() }
	, m_tile_number{ 0 }
	, m_tile_sz{ 0 }
	, m_sheet_sz{ 0 }
	, m_tex_screen_pos{ 0 }
	, m_show_sheet_window{ false }
	, m_reset_tile_images{ false }
	, m_brush_sz{ 1 }
	, m_curr_layer{ 0 }
	, m_mouse_hovering_win{ false }
{

}

void GuiMapEditor::Update()
{
	ImGui::BeginMainMenuBar();
	ImGui::SetCursorPosX(gui::window_data::width - 92);
	if (ImGui::Button("Close editor"))
		util::SwitchBoolean(elem_visibility::show_map_editor);

	SEbool show = true;
	ImGui::SetNextWindowSize(Vec2f(240.0f, 540.0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowPos(Vec2f(0.0f));
	ImGui::Begin("Tilesheets", &show);
	m_mouse_hovering_win = ImGui::IsMouseHoveringWindow();
	for (auto sn : m_tilesheet_names)
	{
		if (ImGui::Button(sn.c_str()))
		{
			m_show_sheet_window = true;
			m_current_tilesheet = m_engine.GetResourceManager().LoadTileSheetResource(sn);
			m_curr_tilesheet_name = sn;
		}
	}
	_tilePropEdit();
	ImGui::Separator();

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
	_sheetPropEdit();

	//Set window
	Vec2f win_sz(
		(m_current_tilesheet->GetData().width < window_data::width * 0.6f) ? m_current_tilesheet->GetData().width : window_data::width * 0.6f,
		(m_current_tilesheet->GetData().heigth < window_data::heigth * 0.9f) ? m_current_tilesheet->GetData().heigth : window_data::heigth * 0.9f
	);

	ImGui::SetNextWindowSize(win_sz, ImGuiSetCond_Always);
	ImGui::SetNextWindowPos(Vec2f(gui::window_data::width / 2.0f - win_sz.x / 2.0f, gui::window_data::heigth / 2.0f - win_sz.y / 2.0f));
	ImGui::Begin(m_curr_tilesheet_name.c_str(), &m_show_sheet_window, ImGuiWindowFlags_HorizontalScrollbar);
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
	if (m_current_tilesheet)
	{

		ImGui::SliderInt("Tile width", &m_current_tilesheet->GetData().tile_width, 1, 512);
		ImGui::SliderInt("Tile heigth", &m_current_tilesheet->GetData().tile_heigth, 1, 512);
		ImGui::SliderInt("Brush size", &m_brush_sz, 1, 5);
		ImGui::SliderInt("Current layer", &m_curr_layer, 0, 5);
		if (ImGui::Button("Reset images"))
			m_curr_tiles_ind = 0;
		m_tile_sz = Vec2u{ m_current_tilesheet->GetData().tile_width, m_current_tilesheet->GetData().tile_heigth };
	}
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
	SEint same_line_counter = 1;
	for (SEint i = 0; i < m_curr_tiles_ind; ++i, same_line_counter++)
	{
		ImGui::PushID(i);
		if (ImGui::ImageButton(
			(void*)static_cast<SEuint64>(m_tiles[i].tex_handle),
			ImVec2(static_cast<SEfloat>(ppu), static_cast<SEfloat>(ppu)),
			ImVec2(m_tiles[i].norm_tex_coords.x, m_tiles[i].norm_tex_coords.y),
			ImVec2(m_tiles[i].norm_tex_coords.z, m_tiles[i].norm_tex_coords.w),
			0
		))
		{
			m_current_tile = m_tiles[i];
		}
		ImGui::PopID();

		if (same_line_counter >= 5)
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
	if (!ImGui::IsMouseClicked(0) && !ImGui::IsMouseDown(0) || m_mouse_hovering_win)
		return;

	Vec2f mousepos = ImGui::GetMousePos();
	Vec2f norm_pos = util::ScreenCoordsToNormOpenGLCoords(mousepos.x, mousepos.y, Vec2i(gui::window_data::width, gui::window_data::heigth), m_engine.GetCamera()->GetPosition());
	Vec2f pos(std::round(norm_pos.x), std::round(norm_pos.y));

	//Check for erasing
	if (mouse.GetState(MouseState::Rigth_Button))
	{
		m_map_creator.RemoveTileFromMap(pos, m_curr_layer);
		return;
	}

	auto data = _checkForTile(pos, Vec2i(m_current_tile.w, m_current_tile.h));
	if (data.first && !data.second)
		m_map_creator.RemoveTileFromMap(pos, m_curr_layer);
	else if (data.second)
		return;

	if (m_brush_sz == 1)
	{
		priv::Tile t = m_current_tile;
		t.position = pos;
		m_map_creator.AddTileToMap(t, m_curr_layer, m_current_tilesheet->name);
	}

	//Handle larger brush sizes

}

std::pair<SEbool, SEbool> GuiMapEditor::_checkForTile(Vec2f position, Vec2i size)
{
	auto data = m_map_creator.CheckForTile(position, size);
	if (data.first)
	{
		if (data.second.x == m_current_tile.x && data.second.y == m_current_tile.y)
			return std::pair<SEbool, SEbool>{true, true};
		return std::pair<SEbool, SEbool>{true, false};
	}
	return{ false, false };
}

}//namespace gui
}//namespace se