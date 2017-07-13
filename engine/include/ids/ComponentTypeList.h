#ifndef SE_COMPONENT_TYPE_LIST_SE
#define SE_COMPONENT_TYPE_LIST_SE


//STL includes:
#include <unordered_map>
#include <string>
#include <utility>

//SE includes:
#include <utility/Typedefs.h>

namespace se
{
///Brief: COMPONENT_TYPE enum contains all components as SEints. When adding new component to engine, add it here also.
///Also add enumeration value and proper name to the map below, so that using gui is possible
enum class COMPONENT_TYPE : SEint
{
	FAULTY_TYPE = -1,
	POSITION,
	VELOCITY,
	SHAPE_CIRCLE,
	SHAPE_RECTANGLE,
	SHAPE_TRIANGLE
};

namespace priv
{
///Brief: Const static map that has COMPONENT_TYPE as key and std::string as value. Used by graphical user interface for showing
///component list of an entity.

static const std::unordered_map<COMPONENT_TYPE, std::string> gui_comp_type_as_string =
{
	{ COMPONENT_TYPE::POSITION, "Position" },
	{ COMPONENT_TYPE::VELOCITY, "Velocity" },
	{ COMPONENT_TYPE::SHAPE_CIRCLE, "ShapeCircle" },
	{ COMPONENT_TYPE::SHAPE_RECTANGLE, "ShapeRectangle" },
	{ COMPONENT_TYPE::SHAPE_TRIANGLE, "ShapeTriangle" }
};
}//namespace priv
}//namespace se

#endif
