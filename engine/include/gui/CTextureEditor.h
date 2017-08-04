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
	CTextureEditor(std::shared_ptr<priv::Engine> engine_ptr);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;

private:
	std::shared_ptr<priv::AnimationSystem> m_animation_sys;
};

}//namespace gui
}//namespace se
#endif