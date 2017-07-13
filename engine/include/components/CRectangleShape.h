#ifndef SE_RECTANGLE_SHAPE_COMPONENT_H
#define SE_RECTANGLE_SHAPE_COMPONENT_H

//Include STL

//Include External
// - TODO: Replace with SE typedefs and remove glm include
#include <glm/glm.hpp>


//Include SE
#include <components/Component.h>
#include <utility/Typedefs.h>

///Brief : baisc rectangle/square shape which is drawn in relation to origin 

namespace se
{
class CRectangleShape : public Component
{

public:
	CRectangleShape(SEfloat size = 1.0f)
		: Component(COMPONENT_TYPE::SHAPE_RECTANGLE)
	{
		SEfloat halfsize = size / 2.0f;
		points.emplace_back(Vec3f(-halfsize, -halfsize, 0.0f));
		points.emplace_back(Vec3f(halfsize, -halfsize, 0.0f));
		points.emplace_back(Vec3f(halfsize, halfsize, 0.0f));
		points.emplace_back(Vec3f(-halfsize, halfsize, 0.0f));
		origin = Vec3f(0.0f);
	}
	CRectangleShape(Vec3f p1, Vec3f p2, Vec3f p3, Vec3f p4)
		: Component(COMPONENT_TYPE::SHAPE_RECTANGLE)
	{
		points.emplace_back(p1);
		points.emplace_back(p2);
		points.emplace_back(p3);
		points.emplace_back(p4);
	}

	std::vector<Vec3f> points;
	Vec3f origin;
};





}//! namespace se


#endif//! SE_RECTANGLE_SHAPE_COMPONENT_H
