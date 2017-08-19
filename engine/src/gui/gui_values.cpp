#include <gui/gui_values.h>

namespace se
{
namespace gui
{
/////Window size for GUI windows
SEint window_data::width = 0;
SEint window_data::heigth = 0;


///Gui elements' visibility indicators
SEbool elem_visibility::show_main_window = true;
SEbool elem_visibility::show_map_editor = false;
SEbool elem_visibility::show_scene_mgr_window = false;
SEbool elem_visibility::show_console_window = false;
SEbool elem_visibility::show_entity_comp_mgr_window = false;
SEbool elem_visibility::show_component_mgr_window = false;


//DEBUG DRAW VALUES
SEbool debug_draw_values::drawGrid = true;
const Vec4f debug_draw_values::color_grid{ 0.0f, 0.0f, 0.0f, 0.3f };
const SEfloat debug_draw_values::grid_z_offset{ -0.05f };

SEbool debug_draw_values::drawAABBs_lines = false;
SEbool debug_draw_values::drawAABBs_points = false;
const Vec4f debug_draw_values::color_AABB{ 1.0f, 1.0f, 0.0f, 0.5f };

SEbool debug_draw_values::drawCollPolys_lines = false;
SEbool debug_draw_values::drawCollPolys_points = false;
const Vec4f debug_draw_values::color_CollPoly{ 0.0f, 1.0f, 0.0f, 0.5f };

SEbool debug_draw_values::drawShapes_lines = false;
SEbool debug_draw_values::drawShapes_points = false;
const Vec4f debug_draw_values::color_Shape{ 0.0f, 0.0f, 1.0f, 0.5f };

 SEbool debug_draw_values::drawPositions = false;
 const Vec4f debug_draw_values::color_pos_points{ 1.0f, 0.0f, 1.0f, 0.5f };


}//namespace gui
}//namespace se
