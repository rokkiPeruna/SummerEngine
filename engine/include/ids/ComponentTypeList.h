#ifndef SUMMER_ENGINE_COMPONENT_TYPE_LIST_SE
#define SUMMER_ENGINE_COMPONENT_TYPE_LIST_SE


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
	TRANSFORMABLE = 0,
	DYNAMIC,
	COLLIDABLE,
	TEXTURE,
	SHAPE,
	ANIMATION,
	GAMELOGIC
};

namespace priv
{
///Brief: Const static map that has COMPONENT_TYPE as key and std::string as value. Used by graphical user interface for showing
///component list of an entity.
static const std::unordered_map<COMPONENT_TYPE, std::string> CompTypeAsString =
{
	{ COMPONENT_TYPE::TRANSFORMABLE, "transformable" },
	{ COMPONENT_TYPE::DYNAMIC, "dynamic" },
	{ COMPONENT_TYPE::COLLIDABLE, "collidable" },
	{ COMPONENT_TYPE::TEXTURE, "texture" },
	{ COMPONENT_TYPE::SHAPE, "shape" },
	{ COMPONENT_TYPE::ANIMATION, "animation" },
	{ COMPONENT_TYPE::GAMELOGIC, "gamelogic" }
};
}//namespace priv
}//namespace se

#endif
