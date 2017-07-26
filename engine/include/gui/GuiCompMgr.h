#ifndef SE_GUICOMPONENTMANAGER_H
#define SE_GUICOMPONENTMANAGER_H


//SE includes:
#include <gui/ManagerGui.h>
#include <managers/EntityManager.h>
#include <managers/ComponentManager.h>

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

	void Update() override final;

private:
	///EntityManager pointer
	priv::EntityManager* m_entity_mgr;

	///ComponentManager pointer
	priv::ComponentManager* m_comp_mgr;
};

}//namespace gui
}//namespace se

#endif