#ifndef SE_COMPONENTSYSTEM_H
#define SE_COMPONENTSYSTEM_H

//STL includes:
#include <vector>
#include <unordered_map>

//SE includes:
#include <utility/Typedefs.h>
#include <components/Component.h>
#include <managers/EntityManager.h>

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

	///AddComponent adds default constructed component of given type to container and adds component's index in that container
	///to Entity's components map. Returns component's index in container. See MovementSystem's implementation for details.
	virtual SEuint AddComponent(Entity&, COMPONENT_TYPE) = 0;

};

}//namespace priv
}//namespace se


#endif