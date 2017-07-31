#ifndef SE_GUI_CCOLLIDABLE_EDITOR_H
#define SE_GUI_CCOLLIDABLE_EDITOR_H

//SE includes:
#include <gui/CompEditorGui.h>

namespace se
{
namespace gui
{
///Brief: SE_TODO: Add description
class CCollidableEditor : public CompEditorGui
{
public:
	///Default constructor
	CCollidableEditor();

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;
};

}//namespace gui
}//namespace se
#endif