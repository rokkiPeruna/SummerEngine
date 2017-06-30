#ifndef SE_TRIANGLE_SHAPE_COMPONENT_H
#define SE_TRIANGLE_SHAPE_COMPONENT_H

//Include STL

//Include External
// - TODO: Replace with SE typedefs and remove glm include
#include <glm/glm.hpp>

//Include SE
#include <components/Component.h>
#include <utility/Typedefs.h>

///Brief : Simple triangle shape which draws its corners in relation to the origin


namespace se
{

class CTriangleShape : public Component
{

public:
	
	// TODO : change glm::vec2 to our typedef asap and delete this comment

	//From either of these we can draw a simple triangle in renderer (I quess..)
	CTriangleShape(SEfloat size = 0.0);
	CTriangleShape(glm::vec2 point_1, glm::vec2 point_2, glm::vec2 point_3);


	///Default destructor
	~CTriangleShape();

	///Copy constructor
	CTriangleShape(const CTriangleShape& copy);

	//Assingment operator
	void operator=(const CTriangleShape& copy) = delete;

	// TODO : Change to our typedef (se)
	glm::vec2 m_point_1;
	glm::vec2 m_point_2;
	glm::vec2 m_point_3;

	SEfloat m_size;
	glm::vec2 m_origin;

private:


};

}//! namespace se


#endif //! SE_TRIANGLE_SHAPE_COMPONENT