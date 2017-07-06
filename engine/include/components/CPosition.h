#ifndef SE_CPOSITION_H
#define SE_CPOSITION_H

//SE includes:
#include <components/Component.h>


namespace se
{
class CPosition : public Component
{
public:
	///Default constructor
	CPosition(SEfloat _x = 0.0f, SEfloat _y = 0.0f, SEfloat _z = 0.0f) 
		: Component(CPosition_id)
		, x(_x)
		, y(_y)
		, z(_z){}

	///Position data as Vec2f
	SEfloat x;
	SEfloat y;
	SEfloat z;
//	Vec2f position;
};
}//namespace se


#endif