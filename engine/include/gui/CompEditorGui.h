#ifndef SUMMER_ENGINE_COMPONENT_EDITOR_GUI_H
#define SUMMER_ENGINE_COMPONENT_EDITOR_GUI_H

//SE includes:
#include <gui/EngineGui.h>
#include <core/Engine.h>
#include <managers/EntityManager.h>

namespace se
{
namespace gui
{
///Brief: Abstract CompEditorGui -class offers common interface for all other classes that handle SE Engine's
///component editors' graphical user interface's functionality.
///It inherits some functionality from EngineGui -class.
///IMPORTANT: Every new component editor must bind itself to correct component type.
///See CTransformableEditor.cpp (ctor implementation) for details!
class CompEditorGui : public EngineGui
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	CompEditorGui(priv::Engine& engine_ref);
	///Destructor
	virtual ~CompEditorGui();
	///No copies allowed
	CompEditorGui(const CompEditorGui&) = delete;
	void operator=(const CompEditorGui&) = delete;

	virtual void Update() {};

	virtual void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj) = 0;

};
}//namespace gui
}//namespace se

#endif