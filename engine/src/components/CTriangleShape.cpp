#include <components/CTriangleShape.h>

namespace se
{

CTriangleShape::CTriangleShape(SEfloat size)
	: Component(CTriangleShape_id)
	, m_points_1(0, size)
	, m_points_2(size, size)
	, m_points_3(-size, size)
{
	
}

CTriangleShape::CTriangleShape(glm::vec2 point_1, glm::vec2 point_2, glm::vec2 point_3)
	: Component(CTriangleShape_id)
	, m_points_1(point_1)
	, m_points_2(point_2)
	, m_points_3(point_3)
{

}

CTriangleShape::~CTriangleShape()
{

}

CTriangleShape::CTriangleShape(const CTriangleShape& copy)
	:Component(CTriangleShape_id)
{
	this->m_size = copy.m_size,
	this->m_points_1 = copy.m_points_1;
	this->m_points_2 = copy.m_points_2;
	this->m_points_3 = copy.m_points_3;
}


}//! namespace se