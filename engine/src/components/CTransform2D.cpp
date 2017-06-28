#include <components/CTransform2D.h>


namespace se
{
CTransform2D::CTransform2D(Vec2f position, Vec2f orientation, Vec2f scale)
	: Component(CTransform2D_id)
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
	: Component(CTransform2D_id)
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
	type = other.type;
	position = other.position;
	orientation = other.orientation;
	scale = other.scale;
	prevPosition = other.position;
	prevOrientation = other.orientation;
	prevScale = other.scale;
	return *this;
}

}//namespace se