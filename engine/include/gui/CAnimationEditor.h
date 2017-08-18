#ifndef SUMMER_ENGINE_CANIMATIONEDITOR_H
#define SUMMER_ENGINE_CANIMATIONEDITOR_H

///STL includes:
#include <vector>

///SE includes:
#include <gui/CompEditorGui.h>

namespace se
{
namespace gui
{
///Brief:
class CAnimationEditor : public CompEditorGui
{
public:
	CAnimationEditor(priv::Engine& engine_ref);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;

private:
	std::vector<std::string> m_anim_res_names;		///Container holding all animations's names for use in gui.
};
}//namespace gui
}//namespace se

#endif