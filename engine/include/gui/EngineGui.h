#ifndef SE_ENGINEGUI_H
#define SE_ENGINEGUI_H

//External includes:
#include <imgui/imgui.h>

//SE includes:


namespace se
{
namespace gui
{
///Brief: EngineGui works as a base class for all other gui classes that partly implementate SE Engine's 
///graphical user interface's functionality. It has few methods for common tasks, like pop up windows
class EngineGui
{
public:
	///Default constructor
	EngineGui();
	///Destructor
	virtual ~EngineGui();
	///No copies allowed
	EngineGui(const EngineGui&) = delete;
	void operator=(const EngineGui&) = delete;



protected:

	// void createPopUpWindow()
};

}//namespace gui
}//namespace se


#endif