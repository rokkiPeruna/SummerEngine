#ifndef SUMMER_ENGINE_GUI_CTRANSFORMABLE_EDITOR_H
#define SUMMER_ENGINE_GUI_CTRANSFORMABLE_EDITOR_H

//SE includes:
#include <gui/CompEditorGui.h>

namespace se
{
namespace gui
{
///Brief: SE_TODO: Add description
class CTransformableEditor : public CompEditorGui
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	CTransformableEditor(priv::Engine& engine_ref);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;
};

}//namespace gui
}//namespace se
#endif