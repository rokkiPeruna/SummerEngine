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


	CRectangleShape(SEfloat size);
	CRectangleShape(glm::vec2 point_1, glm::vec2 point_2, glm::vec2 point_3, glm::vec2 point_4);

	// TODO : Change to our typedef (se)
	glm::vec2 m_point_1;
	glm::vec2 m_point_2;
	glm::vec2 m_point_3;
	glm::vec2 m_point_4;


	SEfloat m_size;
	glm::vec2 m_origin;

private:

};





}//! namespace se


#endif//! SE_RECTANGLE_SHAPE_COMPONENT_H
