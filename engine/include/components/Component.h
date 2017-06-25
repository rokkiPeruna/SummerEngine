#ifndef SE_COMPONENT_H
#define SE_COMPONENT_H

//External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <utility/Typedefs.h>
#include <utility/Math.h>

namespace se
{
///Brief: Component types as enumerations. TODO: This should be somewhere where user can modify it.
enum class COMPONENT_TYPE : SEuint
{
	TRANSFORM,
	PHYSICS
};
namespace priv
{
///Forward declaring ComponentSystem to avoid linking errors
class ComponentSystem;
///Brief: Component -class is a base class for all components.
///Components are POD -classes.
class Component
{
protected:
	///Default constructor. Takes COMPONENT_TYPE as parameter.
	Component(COMPONENT_TYPE type);
public:
	///Destructor
	virtual ~Component();
	///Copy constructor
	Component(const Component& other);
	///Deleted assign operator
	Component& operator=(const Component& other) = delete;

	///Every component has it's type as enum
	COMPONENT_TYPE myType;

	///Boolean for defining if component can overridden in system's component container.
	///Set to false by default.
	bool overwritable;

	///Pointer to owning system
	std::shared_ptr<ComponentSystem> mySystem;

	
};
}//namespace priv
}//namespace se
#endif