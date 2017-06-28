#ifndef SE_CPHYSICS2D_H
#define SE_CPHYSICS2D_H


//SE includes:
#include <components/Component.h>

namespace se
{
///Brief: CPhysics2D -class represents entity's physical properties in 2D space.
class CPhysics2D : public Component
{
public:
	///Default constructor
	CPhysics2D();
	///Destructor
	~CPhysics2D();
	///Copy constructor and assign operator
	CPhysics2D(const CPhysics2D&);
	CPhysics2D& operator=(const CPhysics2D&);
};


}//namespace se
#endif