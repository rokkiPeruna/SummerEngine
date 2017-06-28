#ifndef SE_COMPONENT_H
#define SE_COMPONENT_H

//External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <user/ComponentList.h>

namespace se
{
///Brief: Component types as enumerations. TODO: This should be somewhere where user can modify it.
enum class COMPONENT_TYPE : SEuint
{
	NULL_COMPONENT,
	TRANSFORM,
	PHYSICS
};
///Forward declaring ComponentSystem to avoid linking errors
class ComponentSystem;

///Brief: Component -class is a base class for all components.
///Components are POD -classes.
class Component
{
public:
	///Default constructor. Takes COMPONENT_TYPE as parameter.
	Component(SEuint64 type);
	///Destructor
	virtual ~Component();
	///Copy constructor
	Component(const Component& other);
	///Deleted assign operator
	Component& operator=(const Component& other) = delete;

	///Every component has it's type as SEuint64 bit (see ComponentList.h)
	SEuint64 type;

	///Component's unique id
	SEuint64 id;

	///Boolean for defining if component can overridden in system's component container.
	///Set to false by default.
	bool overwritable;

	///Owner id
	SEuint ownerID;
};
}//namespace se
#endif