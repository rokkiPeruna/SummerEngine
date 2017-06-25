#ifndef SE_COMPONENTSYSTEM_H
#define SE_COMPONENTSYSTEM_H

//STL includes:
#include <initializer_list>

//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>
#include <managers/EntityComponentManager.h>

namespace se
{
namespace priv
{
///Brief: ComponentSystem -class works as a abstract interface class for other
///systems that are responsible for updating components. In addition to pure virtual methods
///described below, every system should have a method for adding a new component to system's component
///container. That method must return shared pointer to the newly created component.
///		Also, in the header file that declares the system, there should be a GLOBAL FREE FUNCTION
///in namespace 'se' that calls for the before-mentioned member method with same parameters. This global free function works
///as a interface for user to add components and must also return a shared pointer to the newly created component.
class ComponentSystem
{
public:
	///Default constructor
	ComponentSystem();
	///Destructor
	virtual ~ComponentSystem();

	///ComponentSystem's initializing method. Takes in shared pointer to EntityComponentManager.
	///Must be overridden in inheriting class.
	virtual void Initialize(std::shared_ptr<EntityComponentManager> ecm_ptr) = 0;

	///ComponentSystem's uninitializing
	///Must be overridden in inheriting class.
	virtual void Uninitialize() = 0;

	///ComponentSystem's update. Takes in (float)deltatime as parameter.
	///Must be overridden in inheriting class.
	virtual void Update(SEfloat deltaTime) = 0;

	///Add new component. TODO: Better description
	virtual std::shared_ptr<Component> CreateNewComponent(std::shared_ptr<Component> component) = 0;

protected:

	///Shared pointer to EntityComponentManager
	std::shared_ptr<EntityComponentManager> m_ecm_ptr;
};

}//namespace priv
}//namespace se


#endif