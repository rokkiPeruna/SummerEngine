#ifndef SE_GUI_CDYNAMIC_EDITOR_H
#define SE_GUI_CDYNAMIC_EDITOR_H

//SE includes:
#include <gui/CompEditorGui.h>
#include <systems/MovementSystem.h>

namespace se
{
namespace gui
{
///Brief: SE_TODO: Add description
class CDynamicEditor : public CompEditorGui
{
public:
	///Default constructor
	CDynamicEditor();

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;
};

}//namespace gui
}//namespace se
#endif