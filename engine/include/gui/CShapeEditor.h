#ifndef SE_GUI_CSHAPE_EDITOR_H
#define SE_GUI_CSHAPE_EDITOR_H

//SE includes:
#include <gui/CompEditorGui.h>

namespace se
{
namespace gui
{
///Brief: SE_TODO: Add description
class CShapeEditor : public CompEditorGui
{
public:
	///Default constructor
	CShapeEditor();

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, nlohmann::json::iterator component_obj) override final;
};

}//namespace gui
}//namespace se
#endif