#ifndef SE_CTRANSFORM_H
#define SE_CTRANSFORM_H

//Include standard library


//Include external


//Include SE
#include <components/Component.h>


///Brief : Transform component is additional context for exisiting components
/// Transform is just a single dot in world coordinates.
namespace se
{
class CTransform : public Component
{
public:


	CTransform(Vec3f rotation = { 0.0f, 0.0f, 0.0f }, Vec3f scale = { 1.0f, 1.0f, 1.0f })
		: Component(COMPONENT_TYPE::TRANSFORM)
		, m_rotation(rotation)
		, m_scale(scale)
	{

	}
	
	
	Vec3f m_rotation;
	Vec3f m_scale;

};



}// !namespace


#endif