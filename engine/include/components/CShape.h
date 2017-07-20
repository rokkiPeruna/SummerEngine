#ifndef SE_CSHAPE_H
#define SE_CSHAPE_H

//Include standard library

//Include external library

//Include se
#include <components/Component.h>


namespace se
{

enum BASIC_SHAPE
{
	TRIANGLE = 1,
	RECTANGLE,
	SQUARE
};


class CShape : public Component
{

public:

	CShape(SEfloat size, BASIC_SHAPE type)
		: Component(COMPONENT_TYPE::FAULTY_TYPE)
	{
		switch (type)
		{
		case BASIC_SHAPE::TRIANGLE:
		{
			SEfloat halfsize = size / 2.0f;
			points.emplace_back(Vec3f(-halfsize, -halfsize, 0.0f));
			points.emplace_back(Vec3f(halfsize, -halfsize, 0.0f));
			points.emplace_back(Vec3f(0.0f, halfsize, 0.0f));
			origin = Vec3f(0.0f);
		}

		case BASIC_SHAPE::RECTANGLE:
		{
			SEfloat halfsize = size / 2.0f;
			points.emplace_back(Vec3f(-halfsize, -halfsize, 0.0f));
			points.emplace_back(Vec3f(halfsize, -halfsize, 0.0f));
			points.emplace_back(Vec3f(halfsize, halfsize, 0.0f));
			points.emplace_back(Vec3f(-halfsize, halfsize, 0.0f));
			origin = Vec3f(0.0f);

		}

		case BASIC_SHAPE::SQUARE:
		{



		}

		}
	}
	std::vector<Vec3f> points;
	Vec3f origin;

private:

};


} // !namespace se


#endif