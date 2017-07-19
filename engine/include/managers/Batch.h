#ifndef SE_BATCH_H
#define SE_BATCH_H

//Standard library includes


//External includes
#include <OpenGL/GLES3/glew.h>

//SE includes
#include <utility/Typedefs.h>


namespace se
{

class Batch
{
public:

	Batch();

	~Batch();

	Batch(const Batch&) = delete;
	void operator=(const Batch&) = delete;

private:

	SEuint VBO;


};


} // !namespace se

#endif