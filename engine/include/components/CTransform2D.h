#ifndef SE_TRANSFORM2DCOMPONENT_H
#define SE_TRANSFORM2DCOMPONENT_H


//SE includes:
#include <components/Component.h>

namespace se
{
///Brief: CTransform2D -class represents entity's transfrom features in 2D coordinates:
///Vec2f position
///Vec2f orientation
///Vec2f scale
///Vec2f prevPosition
///Vec2f prevOrientation
///Vec2f prevScale
class CTransform2D : public Component
{
public:
	///Default constructor
	CTransform2D(Vec2f position = Vec2f(0.0f), Vec2f orientation = Vec2f(0.0f), Vec2f scale = Vec2f(1.0f));
	///Destructor
	~CTransform2D();
	///Copy constructor and assing operator
	CTransform2D(const CTransform2D& other);
	CTransform2D& operator=(const CTransform2D& other);

	///Position
	Vec2f position;

	///Orientation
	Vec2f orientation;

	///Scale
	Vec2f scale;

	///Previous position
	Vec2f prevPosition;

	///Previous orientation
	Vec2f prevOrientation;

	///Previous scale
	Vec2f prevScale;

};
}//namespace se

#endif