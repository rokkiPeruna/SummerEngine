#ifndef SE_CAMERA_H
#define SE_CAMERA_H

//Include Standard library

//Include external

//Include se
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <glm/gtc/matrix_transform.hpp>

namespace se
{

class Camera 
{

public:

	///Default constructor
	Camera();

	///Desturctor
	~Camera();

	///Delete copy constructor and assignment operator
	Camera(const Camera&) = delete;
	void operator=(const Camera&) = delete;

	void Update(const SEfloat deltaTime);

private:

	Vec3f m_cameraPosition;
	Vec3f m_cameraTarget;
	Vec3f m_cameraDirection;

	Vec3f m_cameraRight;
	Vec3f m_cameraUp;

	Mat4f m_view;
};



}// !namespace se


#endif // !camera