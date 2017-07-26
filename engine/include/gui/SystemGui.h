#ifndef SE_SYSTEMGUI_H
#define SE_SYSTEMGUI_H


//SE includes:
#include <gui/EngineGui.h>

namespace se
{
namespace gui
{
///Brief: Abstract SystemGui -class offers common interface for all other classes that handle SE Engine's
///component systems' graphical user interface's functionality.
///It inherits some functionality from EngineGui -class
class SystemGui : public EngineGui
{
public:
	///Default constructor
	SystemGui();
	///Destructor
	virtual ~SystemGui();
	///No copies allowed
	SystemGui(const SystemGui&) = delete;
	void operator=(const SystemGui&) = delete;

	virtual void Update() = 0;

	virtual void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj) = 0;

};
}//namespace gui
}//namespace se

#endif