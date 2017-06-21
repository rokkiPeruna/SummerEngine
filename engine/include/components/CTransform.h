#ifndef SE_TRANSFORMCOMPONENT_H
#define SE_TRANSFORMCOMPONENT_H


//SE includes:
#include <components/Component.h>

namespace se
{
///Brief: CTransform -class represents entity's transfrom features:
class CTransform : public priv::Component
{
public:
	///Default constructor
	CTransform();
	///Destructor
	~CTransform();
	///Copy constructor
	CTransform(const CTransform)
};

}//namespace se

#endif