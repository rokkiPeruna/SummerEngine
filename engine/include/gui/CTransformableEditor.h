#ifndef SE_GUI_CTRANSFORMABLE_EDITOR_H
#define SE_GUI_CTRANSFORMABLE_EDITOR_H

//SE includes:
#include <gui/CompEditorGui.h>
#include <systems/TransformSystem.h>
#include <utility/EditorFunctions.h>

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
	CTransformableEditor(std::shared_ptr<priv::Engine> engine_ptr);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;
};

}//namespace gui
}//namespace se
#endif