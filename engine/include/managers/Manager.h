#ifndef SE_MANAGER_H
#define SE_MANAGER_H

///STL includes:
#include <memory>

//SE includes:
#include <core/Messages.h>
#include <core/SE_exceptions.h>

namespace se
{
namespace priv
{
///Every manager has pointer to engine
class Engine;

///Brief: Manager -class is a abstract base class for all engine managers.
///It demands three pure virtual methods to be overridden:
///Uninitialize()
///Update()
///--
///Initialize() - method parameters varies through managers, so it is not pure virtual.
///If derived manager doesn't override Initialize(), Manager's default method is called.
class Manager
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	Manager(Engine& engine_ref) : m_engine(engine_ref) {}

	///Destructor
	virtual ~Manager() {}

	virtual void Initialize() { MessageInfo(Engine_id) << "Default Initialize() for Manager called"; }

	virtual void Uninitialize() = 0;

	virtual void Update() = 0;

protected:
	///Pointer to engine
	Engine& m_engine;
};

}//namespace priv
}//namespace se



#endif