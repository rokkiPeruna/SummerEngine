#ifndef SE_GUI_CTEXTURE_EDITOR_H
#define SE_GUI_CTEXTURE_EDITOR_H

//SE includes:
#include <gui/CompEditorGui.h>
#include <systems/AnimationSystem.h>

namespace se
{
namespace gui
{
///Brief: SE_TODO: Add description
class CTextureEditor : public CompEditorGui
{
public:
	///Default constructor
	CTextureEditor();

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, nlohmann::json::iterator component_obj) override final;

private:
	priv::AnimationSystem* m_animation_sys;
};

}//namespace gui
}//namespace se
#endif