#ifndef SE_COMPONENTSYSTEM_H
#define SE_COMPONENTSYSTEM_H


//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>
#include <managers/EntityComponentManager.h>
//#include <core/Dictionaries.h>

namespace se
{
namespace priv
{
///Brief: ComponentSystem -class works as a abstract interface class for other
///systems that are responsible for updating components
class ComponentSystem
{
public:
	///Default constructor. Takes in dictionaries
	ComponentSystem();
	///Destructor
	virtual ~ComponentSystem();

	///ComponentSystem's initializing method.
	///Must be overridden in inheriting class.
	virtual void Initialize() = 0;

	///ComponentSystem's uninitializing
	///Must be overridden in inheriting class.
	virtual void Uninitialize() = 0;

	///ComponentSystem's update. Takes in (float)deltatime as parameter.
	///Must be overridden in inheriting class.
	virtual void Update(SEfloat deltaTime) = 0;

protected:

	///Shared pointer to EntityComponentManager
	std::shared_ptr<EntityComponentManager> m_ecm_ptr;

};

}//namespace priv
}//namespace se


#endif