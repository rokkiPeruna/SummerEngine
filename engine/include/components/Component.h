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
///Components are POD -classes.
class Component
{
public:
	///Default constructor. Takes COMPONENT_TYPE as parameter.
	Component(COMPONENT_TYPE type = COMPONENT_TYPE::FAULTY_TYPE);
	///Destructor
	virtual ~Component();
	///Copy constructor
	Component(const Component& other);
	///Deleted assign operator
	Component& operator=(const Component& other) = delete;

	///Every component has it's type as enum class COMPONENT_TYPE (see ComponentList.h)
	COMPONENT_TYPE type;

	///Component's unique id
	SEuint id;

	///Boolean for defining if component can overridden in system's component container.
	///Set to false by default.
	bool overwritable;

	///Owner id
	SEuint ownerID;
};
}//namespace se
#endif