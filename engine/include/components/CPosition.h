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
	CPosition(Vec2f position = Vec2f(0.0f)) 
		: Component(CPosition_id)
		, position(position){}

	///Position data as Vec2f
	Vec2f position;
};
}//namespace se


#endif