#include <gui/GuiMapEditor.h>
#include <core/Window.h>
#include <managers/ResourceManager.h>

namespace se
{
namespace gui
{

GuiMapEditor::GuiMapEditor(priv::Engine& engine_ref)
	: m_engine(engine_ref)
	, m_rel_filep_tilesheets(engine_ref.GetRelFilePathToUserFiles() + "resources/tilesheets/")
	, m_tilesheet_names{ engine_ref.GetResourceManager().GetTileSheetNames() }
{

}


void GuiMapEditor::Update()
{
	static SEbool show_sheet_window = false;

	//ImGui::SetNextWindowSize(ImVec2(window_data::width, window_data::heigth), ImGuiSetCond_Always);
	//ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::BeginMainMenuBar();
	if (ImGui::Button("Close editor"))
		util::SwitchBoolean(elem_visibility::show_map_editor);

	{
		SEbool show = true;
		ImGui::Begin("Tilesheets", &show, Vec2f(70.0f, 100.0f));
		for (auto sn : m_tilesheet_names)
		{
			if (ImGui::Button(sn.c_str()))
				show_sheet_window = true;

			if(show_sheet_window)
			{
				auto res = m_engine.GetResourceManager().LoadTileSheetResource(sn);
				ImGui::SetNextWindowSize(Vec2f(res->GetData().width, res->GetData().width), ImGuiSetCond_Appearing);
				ImGui::SetNextWindowPos(Vec2f(gui::window_data::width / 2.0f - res->GetData().width / 2.0f, gui::window_data::heigth / 2.0f - res->GetData().heigth / 2.0f));
				ImGui::Begin("Sheet", &show_sheet_window);

				ImGui::GetWindowDrawList()->AddImage(
					(void*)static_cast<SEuint64>(res->GetData().handle),
					Vec2f(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y),
					Vec2f(ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y)
				);
				ImGui::Image(
					(void*)static_cast<SEuint64>(res->GetData().handle),
					ImVec2(static_cast<SEfloat>(res->GetData().width), static_cast<SEfloat>(res->GetData().heigth)));

				ImGui::End();

			}
		}
		ImGui::End();
	}

	ImGui::EndMainMenuBar();

}

}//namespace gui
}//namespace se