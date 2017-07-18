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
///REMEMBER: Also add enumeration value and proper name to the map below, so that using gui is possible and serialization/deserialization of data works properly
enum class COMPONENT_TYPE : SEint
{
	FAULTY_TYPE = -1,
	MOVABLE = 0,
	NONMOVABLE = 0, //By defining  nomovable component to same enum as movable, we can prevent entity from having both components! OLET TÄSSÄ
	POSITION,
	VELOCITY,
	ACCELERATION,
	SHAPE,
	TRANSFORM
};

namespace priv
{
///Brief: Const static map that has COMPONENT_TYPE as key and std::string as value. Used by graphical user interface for showing
///component list of an entity.
static const std::unordered_map<COMPONENT_TYPE, std::string> CompTypeAsString =
{
	{ COMPONENT_TYPE::MOVABLE, "movable" },
	{ COMPONENT_TYPE::POSITION, "position" },
	{ COMPONENT_TYPE::VELOCITY, "velocity" },
	{ COMPONENT_TYPE::ACCELERATION, "acceleration"},
	{ COMPONENT_TYPE::TRANSFORM, "transform"}
};
}//namespace priv
}//namespace se

#endif
