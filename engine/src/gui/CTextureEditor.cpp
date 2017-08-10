#include <gui/CTextureEditor.h>
#include <components/CTexture.h>

namespace se
{
namespace gui
{
CTextureEditor::CTextureEditor(priv::Engine& engine_ref)
	: CompEditorGui(engine_ref)
	, m_animation_sys(nullptr)
{
	//This is IMPORTANT. It binds component to correct editor.
	//MUST be done in every new component editor's constructor
	//ALSO remember to add editor to Engine::m_engine_gui_container in Engine::_initGui()
	GraphicalUserInterface::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::TEXTURE, this);

	m_animation_sys = &m_engine.GetAnimationSystem();
	assert(m_animation_sys);
}

void CTextureEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	if (type == COMPONENT_TYPE::TEXTURE)
	{
		if (ImGui::CollapsingHeader("Add texture"))
		{
			Entity* tmpEntity = m_engine.GetEntityMgr().GetCurrentEntity();
			priv::Render* tmpRender = m_engine.GetCurrentRenderer();

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
		else if (ImGui::CollapsingHeader("Change pos and loc"))
		{
			auto tex = GetTextureComponent(index_in_container);
			
			ImGui::SliderInt("X", &tex->x, 0, tex->parent_img_w - tex->width);
			ImGui::SliderInt("Y", &tex->y, 0, tex->parent_img_h - tex->heigth);

			ImGui::SliderInt("Width", &tex->width, 0, tex->parent_img_w - tex->x);
			ImGui::SliderInt("Heigth", &tex->heigth, 0, tex->parent_img_h - tex->y);

			component_obj.value().at("x") = tex->x;
			component_obj.value().at("y") = tex->y;
			component_obj.value().at("w") = tex->width;
			component_obj.value().at("h") = tex->heigth;
		}
		else if (ImGui::CollapsingHeader("Image"))
		{
			ImGui::BeginChild("Imagedata", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
			auto tex = GetTextureComponent(index_in_container);

			ImGui::GetWindowDrawList()->AddImage(
				(void*)static_cast<SEuint64>(tex->handle),
				Vec2f(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y),
				Vec2f(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y)
			);
			ImGui::Image(
				&tex->handle,
				ImVec2(static_cast<SEfloat>(tex->parent_img_w), static_cast<SEfloat>(tex->parent_img_h))
			);

			ImGui::EndChild();
		}
	}
}

}//namespace gui
}//namespace se