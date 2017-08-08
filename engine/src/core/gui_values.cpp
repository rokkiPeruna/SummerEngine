#include <core/gui_values.h>

namespace se
{
namespace gui
{
/////Window size for GUI windows
//const SEint win_width = 1200;
//const SEint win_heigth = 800;
//
/////Main window
//static SEbool show_main_window = true;
//
/////Scene manager
//static SEbool show_scene_mgr_window = false;
//
//
/////Console
//static SEbool show_console_window = false;
//
/////EntityComponent manager
//static SEbool show_entity_comp_mgr_window = false;
//
/////Component manager
//static SEbool show_component_mgr_window = false;

//DEBUG DRAW VALUES
SEbool debug_draw_values::drawAABBs = false;
const Vec4f debug_draw_values::color_AABB{ 1.0f, 1.0f, 0.0f, 1.0f };

SEbool debug_draw_values::drawCollPolys = false;
const Vec4f debug_draw_values::color_CollPoly{ 0.0f, 1.0f, 0.0f, 1.0f };

SEbool debug_draw_values::drawShapes = false;
const Vec4f debug_draw_values::color_Shape{ 0.0f, 0.0f, 1.0f, 1.0f };

}//namespace gui
}//namespace se
