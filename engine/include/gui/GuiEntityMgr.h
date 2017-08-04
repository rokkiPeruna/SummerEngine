#ifndef SE_GUIENTITYMANAGER_H
#define SE_GUIENTITYMANAGER_H


//SE includes:
#include <gui/ManagerGui.h>
#include <managers/EntityManager.h>
#include <managers/ComponentManager.h>

namespace se
{
namespace gui
{
class GuiCompMgr;

///Brief:	...
class GuiEntityMgr : public ManagerGui
{
public:
	///Default constructor.
	///1.param: const ptr to Engine -class
	GuiEntityMgr(priv::Engine* engine_ptr);
	///Destructor
	~GuiEntityMgr();
	///No copies allowed
	GuiEntityMgr(const GuiEntityMgr&) = delete;
	void operator=(const GuiEntityMgr&) = delete;

	void Update() override final;

private:
	///EntityManager pointer
	priv::EntityManager* m_entity_mgr;
	
	///ComponentManager pointer
	priv::ComponentManager* m_comp_mgr;

	///GuiCompMgr pointer
	GuiCompMgr* m_gui_comp_mgr;

	std::string m_gui_scene_name;

};

}//namespace gui
}//namespace se

#endif