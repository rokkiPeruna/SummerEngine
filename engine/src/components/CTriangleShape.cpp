#include <components/CTriangleShape.h>

namespace se
{

CTriangleShape::CTriangleShape(SEfloat size)
	: Component(CTriangleShape_id)
	, m_size(size)
	, m_origin( glm::vec2(0.0f, 0.0f) )
	, m_point_1( 0, 0 + size)
	, m_point_2( 0 + size, 0 - size)
	, m_point_3( 0 - size, 0 - size)
{

}

CTriangleShape::CTriangleShape(glm::vec2 point_1, glm::vec2 point_2, glm::vec2 point_3)
	: Component(CTriangleShape_id)
	, m_origin(0, 0)
	, m_point_1(point_1)
	, m_point_2(point_2)
	, m_point_3(point_3)
{

}

CTriangleShape::~CTriangleShape()
{

}

CTriangleShape::CTriangleShape(const CTriangleShape& copy)
	:Component(CTriangleShape_id)
{
	this->m_origin = copy.m_origin;
	this->m_size = copy.m_size;
	this->m_point_1 = copy.m_point_1;
	this->m_point_2 = copy.m_point_2;
	this->m_point_3 = copy.m_point_3;

}

}//! namespace se