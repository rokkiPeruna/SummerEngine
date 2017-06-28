#ifndef SE_CVELOCITY_H
#define SE_CVELOCITY_H

//SE includes:
#include <components/Component.h>


namespace se
{
class CVelocity : public Component
{
public:
	///Default constructor
	CVelocity(Vec2f velocity = Vec2f(0.0f)) 
		: Component(CVelocity_id)
		, velocity(velocity) {}

	///Position data as Vec2f
	Vec2f velocity;
};
}//namespace se


#endif