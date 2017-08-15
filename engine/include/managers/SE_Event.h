#ifndef SE_SEEVENT_H
#define SE_SEEVENT_H

///SE includes:
#include <utility/Math.h>
#include <utility/Typedefs.h>

namespace se
{
class SE_Event
{
public:
	SE_Event(){}


};

class OnTransformChanged : public SE_Event
{
public: 
	OnTransformChanged(SEint transf_id, Mat4f new_mod_mat)
		: transform_id(transf_id)
		, new_model_matrix(new_mod_mat)
	{

	}

	SEint transform_id;
	Mat4f new_model_matrix;

};

}//namespace se
#endif