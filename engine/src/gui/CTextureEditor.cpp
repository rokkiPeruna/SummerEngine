#include <gui/CTextureEditor.h>
#include <core/Engine.h>
#include <components/CTexture.h>

namespace se
{
namespace gui
{
CTextureEditor::CTextureEditor(priv::Engine* engine_ptr)
	: CompEditorGui(engine_ptr)
	, m_animation_sys(nullptr)
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	priv::Engine::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::TEXTURE, this);

	m_animation_sys = m_engine->GetAnimationSystem();
	assert(m_animation_sys);
}

void CTextureEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::TEXTURE)
	{
		if (ImGui::CollapsingHeader("Add texture"))
		{
			Entity* tmpEntity = priv::Engine::Instance().GetEntityMgr()->GetCurrentEntity();
			priv::Render* tmpRender = priv::Engine::Instance().GetCurrentRenderer();

			if (m_animation_sys->GetTextureResourceNames().empty())
			{
				MessageInfo(AnimationSys_id) << "No available texture resources in ModifyComponent!";
				return;
			}

			//Get available textures
			for (auto t_n : m_animation_sys->GetTextureResourceNames())
			{
				if (ImGui::Button(t_n.c_str()))
				{
					tmpRender->OnRendableComponentChanged(*tmpEntity);
				
					m_animation_sys->AssignTexture(t_n, *GetTextureComponent(index_in_container));
					component_obj.value().at("tex_name") = t_n;
					
					tmpRender->OnEntityAdded(*tmpEntity);
				}
			}
		}
	}
}

}//namespace gui
}//namespace se