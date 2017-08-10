#ifndef SE_GUICOMPONENTMANAGER_H
#define SE_GUICOMPONENTMANAGER_H


//SE includes:
#include <gui/ManagerGui.h>
#include <managers/SceneManager.h>
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
	///Default constructor.
	///1.param: reference to Engine -class
	GuiCompMgr(priv::Engine& engine_ref, SEuint update_priority);
	///Destructor
	~GuiCompMgr();
	///No copies allowed
	GuiCompMgr(const GuiCompMgr&) = delete;
	void operator=(const GuiCompMgr&) = delete;

	void Update() override final;

	void InvalidateComponentObj();

private:
	///SceneManager pointer
	priv::SceneManager* m_scene_mgr;

	///EntityManager pointer
	priv::EntityManager* m_entity_mgr;

	///ComponentManager pointer
	priv::ComponentManager* m_comp_mgr;

	///Need reinit?
	SEbool m_reInitWithNewComp;

	///Initialize with new component
	void _initWithNewComp();

	///
	nlohmann::json::iterator m_component_obj;

	///
	Component* m_curr_component;
	SEint m_curr_comp_index;
};

}//namespace gui
}//namespace se

#endif