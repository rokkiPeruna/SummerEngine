#ifndef SE_GUI_CGAME_LOGIC_EDITOR_H
#define SE_GUI_CGAME_LOGIC_EDITOR_H

//include standard library

//include external

//include se
#include <gui/CompEditorGui.h>

namespace se
{
namespace gui
{
class CGameLogicEditor : public CompEditorGui
{
//mit‰ miell‰ on.. monta ClogicComponent -> voi sis‰lt‰‰ monta logiikka palikka
//vain 1 palikka voi olla kerrallaan aktiivinne? 

public:
	///Default constructor
	///1.param pointer to Engine -class
	CGameLogicEditor(priv::Engine& engine_ref);

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) override final;

private:
	std::vector<std::string> allLogicNames;
};

}//! namespace gui

}//! namespace se


#endif//! SE_GUI_CGAME_LOGIC_EDITOR_H