#include <gui/CAnimationEditor.h>
#include <systems/AnimationSystem.h>
#include <managers/ResourceManager.h>

namespace se
{
namespace gui
{
CAnimationEditor::CAnimationEditor(priv::Engine& engine_ref)
	: CompEditorGui(engine_ref)
	, m_anim_res_names{}
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	GraphicalUserInterface::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::ANIMATION, this);

	///Fetch animation names
	m_anim_res_names = m_engine.GetResourceManager().GetAnimationNames();
}

void CAnimationEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::ANIMATION)
	{
		//Add already existing animation
		if (ImGui::CollapsingHeader("Add animation"))
		{
			for (auto& aname : m_anim_res_names)
			{
				if (ImGui::Button(aname.c_str()))
				{
					auto& anim_comp = *GetAnimationComponent(index_in_container);
					if (!anim_comp.animation_names.count(aname))
					{
						m_engine.GetAnimationSystem().AssingAnimation(aname, anim_comp);
					}
				}	
			}
		}
		if (ImGui::CollapsingHeader("Create animation"))
		{
			//
		}
	}
}

}//namespace gui
}//namespace se