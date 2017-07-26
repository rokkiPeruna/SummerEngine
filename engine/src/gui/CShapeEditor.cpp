#include <gui/CShapeEditor.h>
#include <core/Engine.h>
#include <components/CShape.h>

namespace se
{
namespace gui
{
CShapeEditor::CShapeEditor()
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	priv::Engine::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::SHAPE, this);
}

void CShapeEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{
	Message(_nullSysMgr_id) << "CShapeEditor";
}

}//namespace gui
}//namespace se