#ifndef SE_TRIANGLE_SHAPE_COMPONENT_H
#define SE_TRIANGLE_SHAPE_COMPONENT_H

//SE includes
#include <components/Component.h>

namespace se
{
class CTriangleShape : public Component
{
public:
	CTriangleShape(SEfloat size = 1.0)
		: Component(COMPONENT_TYPE::FAULTY_TYPE)
	{
		SEfloat halfsize = size / 2.0f;
		points.emplace_back(Vec3f(-halfsize, -halfsize, 0.0f));
		points.emplace_back(Vec3f(halfsize, -halfsize, 0.0f));
		points.emplace_back(Vec3f(0.0f, halfsize, 0.0f));
		origin = Vec3f(0.0f);
	}
	CTriangleShape(Vec3f p1, Vec3f p2, Vec3f p3)
		: Component(COMPONENT_TYPE::FAULTY_TYPE)
	{
		points.emplace_back(p1);
		points.emplace_back(p2);
		points.emplace_back(p3);
		origin = Vec3f(0.0f);
	}

	

	std::vector<Vec3f> points;
	Vec3f origin;
};
}//namespace se


#endif //! SE_TRIANGLE_SHAPE_COMPONENT