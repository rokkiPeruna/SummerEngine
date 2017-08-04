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
	///Default constructor.
	///1.param: pointer to Engine -class
	CTextureEditor(priv::Engine& engine_ref);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;

private:
	priv::AnimationSystem* m_animation_sys;
};

}//namespace gui
}//namespace se
#endif