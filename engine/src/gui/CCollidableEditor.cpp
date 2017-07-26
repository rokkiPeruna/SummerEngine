#include <gui/CCollidableEditor.h>
#include <core/Engine.h>
#include <components/CCollidable.h>

namespace se
{
namespace gui
{
CCollidableEditor::CCollidableEditor()
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	priv::Engine::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::COLLIDABLE, this);
}

void CCollidableEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{
	Message(_nullSysMgr_id) << "CCollidableEditor";
}

}//namespace gui
}//namespace se