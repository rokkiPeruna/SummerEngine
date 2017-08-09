///Brief: gui_values.h contains values that are used by graphical user interface.

#ifndef SE_GUI_VALUES_H
#define SE_GUI_VALUES_H



//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>

namespace se
{
namespace gui
{
///Window size for GUI windows
const SEint win_width = 1200;
const SEint win_heigth = 800;

///Main window
static SEbool show_main_window = true;

///Scene manager
static SEbool show_scene_mgr_window = false;


///Console
static SEbool show_console_window = false;

///EntityComponent manager
static SEbool show_entity_comp_mgr_window = false;

///Component manager
static SEbool show_component_mgr_window = false;

//DEBUG DRAW VALUES
static struct debug_draw_values
{
	static SEbool drawAABBs_lines;
	static SEbool drawAABBs_points;
	static const Vec4f color_AABB;

	static SEbool drawCollPolys_lines;
	static SEbool drawCollPolys_points;
	static const Vec4f color_CollPoly;

	static SEbool drawShapes_lines;
	static SEbool drawShapes_points;
	static const Vec4f color_Shape;

	static SEbool drawPositions;
	static const Vec4f color_pos_points;
};

}//namespace gui
}//namespace se




#endif