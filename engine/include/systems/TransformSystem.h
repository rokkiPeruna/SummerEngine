#ifndef SE_TRANSFORM_SYSTEM_H
#define SE_TRANSFORM_SYSTEM_H

//Include standard library

//Include external

//Include SE
#include <systems/ComponentSystem.h>

namespace se
{
namespace priv
{



class TransformSystem : public ComponentSystem
{

public:

	TransformSystem();

	~TransformSystem();

	TransformSystem(const TransformSystem&) = delete;
	void operator=(const TransformSystem&) = delete;


private:


};


} // !namespace priv

} // !namespace se


#endif