#ifndef SE_MANAGER_H
#define SE_MANAGER_H


//SE includes:
#include <core/Messages.h>
#include <core/SE_exceptions.h>


namespace se
{
namespace priv
{
///Brief: Manager -class is a abstract base class for all engine managers.
///It demands three pure virtual methods to be overridden:
///Uninitialize()
///Update()
///ShowAndUpdateGUI()
///--
///Initialize() - method parameters varies through managers, so it is not pure virtual.
///If derived manager doesn't override Initialize(), Manager's default method is called.
class Manager
{
public:
	///Default constructor
	Manager(){}

	virtual void Initialize() { MessageInfo(Engine_id) << "Default Initialize() for Manager called"; }

	virtual void Uninitialize() = 0;

	virtual void Update() = 0;

	virtual void ShowAndUpdateGUI() = 0;
};

}//namespace priv
}//namespace se



#endif