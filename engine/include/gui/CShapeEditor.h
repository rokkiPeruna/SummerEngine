#ifndef SUMMER_ENGINE_GUI_CSHAPE_EDITOR_H
#define SUMMER_ENGINE_GUI_CSHAPE_EDITOR_H

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
	///Default constructor.
	///1.param: pointer to Engine -class
	CShapeEditor(priv::Engine& engine_ref);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;
};

}//namespace gui
}//namespace se
#endif