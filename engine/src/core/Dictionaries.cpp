#include <core/Dictionaries.h>
#include <core/Engine.h>

///SE includes:
#include <components/NullComponent.h>


namespace se
{
///Brief: Function for initializing static Engine::componentDictionaries in Engine::Initialize().
///Note:
///If user
//ComponentDictionary initComponentDictionary()
//{
//	ComponentDictionary tmp
//	(
//	{
//		{ COMPONENT_TYPE::TRANSFORM, std::type_index(typeid(CTransform2D)) },
//		{ COMPONENT_TYPE::PHYSICS, std::type_index(typeid(CPhysics2D)) }
//	}
//	);
//	return tmp;
//}

///Brief: Function for initializing static Engine::systemForComponentDictionary in Engine::Initialize()
//SystemForComponentDictionary initSystemForComponentDictionary(priv::Engine& engine)
//{
//	SystemForComponentDictionary tmp
//	(
//	{
//		{ COMPONENT_TYPE::TRANSFORM, engine.GetTransformSystem() }
//	}
//	);
//	return tmp;
//}

}//namespace se