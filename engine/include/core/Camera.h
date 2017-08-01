#ifndef SE_CAMERA_H
#define SE_CAMERA_H

//Include Standard library

//Include external

//Include se
#include <utility/Typedefs.h>
#include <utility/Math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <managers/Keyboard.h>

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

	///Update camera position
	void Update(const SEfloat deltaTime);

	///Get view matrix
	Mat4f GetCameraView();

private:

	///Keyboard for input handling
	Keyboard m_keyboard;

	///Where is the camera
	Vec3f m_cameraPosition;
	
	///Target of the camera, what is it looking at
	Vec3f m_cameraTarget;

	///Direction of the camera 
	Vec3f m_cameraDirection;

	///View matrix
	Mat4f m_view;

	///Right side vector from cameras point of view
	Vec3f m_cameraRight;

	///Up side vector from cameras point of view
	Vec3f m_cameraUp;
	
	///Front direction (default -1.0f in Z axis)
	Vec3f m_cameraFront;
};



}// !namespace se


#endif // !camera