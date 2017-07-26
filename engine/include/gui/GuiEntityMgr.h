#ifndef SE_GUIENTITYMANAGER_H
#define SE_GUIENTITYMANAGER_H


//SE includes:
#include <gui/ManagerGui.h>

namespace se
{
namespace gui
{
///Brief:	...
class GuiEntityMgr : public ManagerGui
{
public:
	///Default constructor
	GuiEntityMgr();
	///Destructor
	~GuiEntityMgr();
	///No copies allowed
	GuiEntityMgr(const GuiEntityMgr&) = delete;
	void operator=(const GuiEntityMgr&) = delete;

	void Update() override final{}

};

}//namespace gui
}//namespace se

#endif