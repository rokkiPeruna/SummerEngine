#ifndef SE_COMPONENTSYSTEM_H
#define SE_COMPONENTSYSTEM_H


namespace se
{
namespace priv
{
///Brief: ComponentSystem -class works as a abstract interface class for other
///systems responsible for updating components
class ComponentSystem
{
public:
	///Default constructor
	ComponentSystem() {}
	///Destructor
	virtual ~ComponentSystem() {}

	///ComponentSystem's initializing method.
	///Must be overridden in inheriting class.
	virtual void Initialize() = 0;

	///ComponentSystem's uninitializing
	///Must be overridden in inheriting class.
	virtual void Uninitialize() = 0;

	///ComponentSystem's update. Takes in (float)deltatime as parameter.
	///Must be overridden in inheriting class.
	virtual void Update(float deltaTime) = 0;

};

}//namespace priv
}//namespace se


#endif