#ifndef SE_COMPONENT_H
#define SE_COMPONENT_H

//External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <ids/ComponentTypeList.h>

namespace se
{
///Forward declaring ComponentSystem to avoid linking errors
class ComponentSystem;

///Brief: Component -class is a base class for all components.
///Components are POD -classes. Every deriving component must be DefaultConstructable.
class Component
{
public:
	///Default constructor. Takes COMPONENT_TYPE as parameter.
	Component(COMPONENT_TYPE type)
		: type(type)
		, id(0)
		, ownerID(0) {}

	///Every component has it's type as enum from COMPONENT_TYPE (see ComponentTypeList.h)
	COMPONENT_TYPE type;

	///Component's unique id
	SEuint id;

	///Owner id
	SEuint ownerID;
};
}//namespace se
#endif