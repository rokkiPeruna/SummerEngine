#ifndef SE_GUICOMPONENTMANAGER_H
#define SE_GUICOMPONENTMANAGER_H


//SE includes:
#include <gui/ManagerGui.h>

namespace se
{
namespace gui
{
///Brief:	...
class GuiCompMgr : public ManagerGui
{
public:
	///Default constructor
	GuiCompMgr();
	///Destructor
	~GuiCompMgr();
	///No copies allowed
	GuiCompMgr(const GuiCompMgr&) = delete;
	void operator=(const GuiCompMgr&) = delete;

	void Update() override final {}

};

}//namespace gui
}//namespace se

#endif