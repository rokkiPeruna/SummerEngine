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
///REMEMBER: Also add enumeration value and proper name to the map below, so that using gui is possible and serialization/deserialization works properly
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
static const std::unordered_map<COMPONENT_TYPE, std::string> CompTypeAsString =
{
	{ COMPONENT_TYPE::POSITION, "position" },
	{ COMPONENT_TYPE::VELOCITY, "velocity" },
	{ COMPONENT_TYPE::SHAPE_CIRCLE, "shape_circle" },
	{ COMPONENT_TYPE::SHAPE_RECTANGLE, "shape_rectangle" },
	{ COMPONENT_TYPE::SHAPE_TRIANGLE, "shape_triangle" }
};
}//namespace priv
}//namespace se

#endif
