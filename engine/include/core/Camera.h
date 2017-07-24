#ifndef SE_CAMERA_H
#define SE_CAMERA_H

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


private:

};



}// !namespace se


#endif // !camera