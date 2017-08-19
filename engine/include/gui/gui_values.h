///Brief: gui_values.h contains values that are used by graphical user interface.

#ifndef SUMMER_ENGINE_GUI_VALUES_H
#define SUMMER_ENGINE_GUI_VALUES_H



//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>

namespace se
{
namespace gui
{
///Window size for GUI windows
struct window_data
{
	static SEint width;
	static SEint heigth;
};

///Gui elements' visibility indicators
struct elem_visibility
{
	///Main window
	static SEbool show_main_window;
	///Map editor
	static SEbool show_map_editor;
	///Scene manager
	static SEbool show_scene_mgr_window;
	///Console
	static SEbool show_console_window;
	///EntityComponent manager
	static SEbool show_entity_comp_mgr_window;
	///Component manager
	static SEbool show_component_mgr_window;
};

//DEBUG DRAW VALUES
struct debug_draw_values
{
	static SEbool drawGrid;
	static const Vec4f color_grid;
	static const SEfloat grid_z_offset;

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