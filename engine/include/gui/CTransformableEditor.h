#ifndef SE_GUI_CTRANSFORMABLE_EDITOR_H
#define SE_GUI_CTRANSFORMABLE_EDITOR_H

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
	///Default constructor
	CTransformableEditor();

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj) override final;
};

}//namespace gui
}//namespace se
#endif