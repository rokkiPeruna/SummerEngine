#include <components/CPhysics2d.h>


namespace se
{
CPhysics2D::CPhysics2D()
	:Component(CPhysics2D_id)
{

}

CPhysics2D::~CPhysics2D()
{

}

CPhysics2D::CPhysics2D(const CPhysics2D& other)
	:Component(CPhysics2D_id)
{

}

CPhysics2D& CPhysics2D::operator=(const CPhysics2D& other)
{
	type = other.type;

	return *this;
}

}//namespace se