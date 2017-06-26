#ifndef SE_COMPONENTDICTIONARY_H
#define SE_COMPONENTDICTIONARY_H

///STL includes:
#include <unordered_map>
#include <typeindex>
#include <functional>

///SE includes:
#include <components/Component.h>
#include <components/NullComponent.h>
#include <components/CTransform2D.h>
#include <systems/ComponentSystem.h>
#include <systems/TransformSystem.h>
#include <components/CPhysics2d.h>

namespace se
{
///Brief: ComponentDictionary holds pairs of components' enum type and their type_index
typedef std::unordered_map<COMPONENT_TYPE, std::type_index> ComponentDictionary;
static ComponentDictionary componentDictionary
(
{
	{ COMPONENT_TYPE::TRANSFORM, std::type_index(typeid(CTransform2D)) },
	{ COMPONENT_TYPE::PHYSICS, std::type_index(typeid(CPhysics2D)) }
}
);


typedef std::unordered_map < COMPONENT_TYPE, std::function<std::shared_ptr<priv::Component>(priv::ComponentSystem&, priv::Component&)>> ComponentToMethodDictionary; //Katso tätä, pitäisi toimia!!
static ComponentToMethodDictionary c_to_m(
{ 
	{COMPONENT_TYPE::TRANSFORM,  &priv::TransformSystem::InitializeNewComponent}
}
);


///Brief: Dictionary binding component types to correct systems.
typedef std::unordered_map<COMPONENT_TYPE, std::shared_ptr<priv::ComponentSystem>> SystemForComponentDictionary;
static SystemForComponentDictionary sysForCompDictionary
(
{
{ COMPONENT_TYPE::TRANSFORM, nullptr}
}
);


}//namespace se
#endif