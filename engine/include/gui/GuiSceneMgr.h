#ifndef SUMMER_ENGINE_GUISCENEMANAGER_H
#define SUMMER_ENGINE_GUISCENEMANAGER_H


//SE includes:
#include <gui/ManagerGui.h>
#include <managers/SceneManager.h>

namespace se
{
namespace gui
{
///Brief:	...
class GuiSceneMgr : public ManagerGui
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	GuiSceneMgr(priv::Engine& engine_ref, SEuint update_priority);
	//
	~GuiSceneMgr() = default;
	GuiSceneMgr(const GuiSceneMgr&) = delete;
	void operator=(const GuiSceneMgr&) = delete;
	GuiSceneMgr(GuiSceneMgr&&) = delete;
	void operator=(GuiSceneMgr&&) = delete;

	void Update() override final;

private:
	///SceneManager pointer
	priv::SceneManager* m_sceneMgr;

	void _handlePopups();

	SEbool m_gui_sceneAdded;
	SEbool m_gui_addSceneNameConflict;
	SEbool m_gui_sceneAlreadyLoaded;
};

}//namespace gui
}//namespace se

#endif