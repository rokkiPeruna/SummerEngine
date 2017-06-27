#ifndef SE_DICTIONARIES_H
#define SE_DICTIONARIES_H

///STL includes:
#include <unordered_map>
#include <typeindex>
#include <functional>

//SE includes:
#include <components/Component.h>
#include <systems/ComponentSystem.h>

namespace se
{
class Engine;

///Brief: ComponentDictionary holds pairs of components' enum type and their type_index
typedef std::unordered_map<COMPONENT_TYPE, std::type_index> ComponentDictionary;
ComponentDictionary initComponentDictionary();


///Brief: Dictionary binding component types to correct systems.
typedef std::unordered_map<COMPONENT_TYPE, std::shared_ptr<priv::ComponentSystem>> SystemForComponentDictionary;
SystemForComponentDictionary initSystemForComponentDictionary(Engine& engine);

}//namespace se

#endif