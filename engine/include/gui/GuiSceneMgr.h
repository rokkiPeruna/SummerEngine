#ifndef SE_GUISCENEMANAGER_H
#define SE_GUISCENEMANAGER_H


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
	GuiSceneMgr(priv::Engine* engine_ptr);
	///Destructor
	~GuiSceneMgr();
	///No copies allowed
	GuiSceneMgr(const GuiSceneMgr&) = delete;
	void operator=(const GuiSceneMgr&) = delete;

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