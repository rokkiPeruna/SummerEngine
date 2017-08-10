#ifndef SE_COMPSYSTEMEVENTHANDLER_H
#define SE_COMPSYSTEMEVENTHANDLER_H


namespace se
{
namespace priv
{
///Handles events between systems and components, e.g. CDynamic has velocity so CTransformable needs to be informed that 
///model matric needs to be recalculated.
class CompSystemEventHandler
{
public:
	///Default constructor
	CompSystemEventHandler();
	//
	~CompSystemEventHandler() = default;
	CompSystemEventHandler(const CompSystemEventHandler&) = delete;
	void operator=(const CompSystemEventHandler&) = delete;
	CompSystemEventHandler(CompSystemEventHandler&&) = delete;
	void operator=(CompSystemEventHandler&&) = delete;



};


}//namespace priv
}//namespace se

#endif