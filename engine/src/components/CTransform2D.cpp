#include <components/CTransform2D.h>
#include <systems/TransformSystem.h>


namespace se
{

CTransform2D::CTransform2D(Vec2f position, Vec2f orientation, Vec2f scale)
	: priv::Component(COMPONENT_TYPE::TRANSFORM)
	, position(position)
	, orientation(orientation)
	, scale(scale)
	, prevPosition(position)
	, prevOrientation(orientation)
	, prevScale(scale)
{
	
}

CTransform2D::~CTransform2D()
{

}

CTransform2D::CTransform2D(const CTransform2D& other)
	: priv::Component(COMPONENT_TYPE::TRANSFORM)
	, position(other.position)
	, orientation(other.orientation)
	, scale(other.scale)
	, prevPosition(other.position)
	, prevOrientation(other.orientation)
	, prevScale(other.scale)
{
	
}

CTransform2D& CTransform2D::operator=(const CTransform2D& other)
{
	myType = COMPONENT_TYPE::TRANSFORM;
	position = other.position;
	orientation = other.orientation;
	scale = other.scale;
	prevPosition = other.position;
	prevOrientation = other.orientation;
	prevScale = other.scale;
	return *this;
}

}//namespace se