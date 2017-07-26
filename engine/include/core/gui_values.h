///Brief: gui_values.h contains values that are used by graphical user interface.

#ifndef SE_GUI_VALUES_H
#define SE_GUI_VALUES_H



//SE includes:
#include <utility/Typedefs.h>

namespace se
{
namespace gui
{
///Window size for GUI windows
const SEint _gui_width = 1200;
const SEint _gui_heigth = 800;

///Main window
static SEbool _gui_show_main_window = true;

///Scene manager
static SEbool _gui_show_scene_mgr_window = false;


///Console
static SEbool _gui_show_console_window = false;

///EntityComponent manager
static SEbool _gui_show_entity_comp_mgr_window = false;

///Component manager
static SEbool _gui_show_component_mgr_window = false;

}//namespace priv
}//namespace se




#endif