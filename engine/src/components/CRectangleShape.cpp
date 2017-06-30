#include <components/CRectangleShape.h>

namespace se
{
CRectangleShape::CRectangleShape(SEfloat size)
	: Component(CRectangleShape_id)
	, m_size(size)
	, m_origin(0, 0)
	, m_point_1(0 - size, 0 + size)
	, m_point_2(0 + size, 0 + size)
	, m_point_3(0 + size, 0 - size)
	, m_point_4(0 - size, 0 - size)
{

}

CRectangleShape::CRectangleShape(glm::vec2 point_1, glm::vec2 point_2, glm::vec2 point_3, glm::vec2 point_4)
	: Component(CRectangleShape_id)
{



}
}//! namespace se