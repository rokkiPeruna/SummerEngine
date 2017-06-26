#include <components/CPhysics2d.h>


namespace se
{
CPhysics2D::CPhysics2D()
	:Component(COMPONENT_TYPE::PHYSICS)
{

}

CPhysics2D::~CPhysics2D()
{

}

CPhysics2D::CPhysics2D(const CPhysics2D& other)
	:Component(COMPONENT_TYPE::PHYSICS)
{

}

CPhysics2D& CPhysics2D::operator=(const CPhysics2D& other)
{
	myType = COMPONENT_TYPE::PHYSICS;

	return *this;
}

}//namespace se