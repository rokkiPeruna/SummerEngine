#include <gui/CGameLogicEditor.h>
#include <systems/GameLogicSystem.h>
#include <AddLogicToEngine.h>

namespace se
{
namespace gui
{

CGameLogicEditor::CGameLogicEditor(priv::Engine& engine_ref)
	: CompEditorGui(engine_ref)
	, allLogicNames()
{
	GraphicalUserInterface::ComponentTypeToGuiEditor.emplace(COMPONENT_TYPE::GAMELOGIC, this);
	for (auto i : priv::GameLogicInstances)
	{
		allLogicNames.emplace_back(i->GetName());
	}
}


void CGameLogicEditor::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, Dataformat_itr component_obj)
{
	//Make sure that the component has Game logic component
	if ((type == COMPONENT_TYPE::GAMELOGIC))
	{
		//Since we already have the knowlege of all 'real' names of possible 
		//game logic instances we can use those
		//note: these are not directly related to the actual file names, but 
		//to the instances of those classes
		auto exsisting = GetGameLogicComponent(index_in_container);


		//Run through all instances
		//we should check if the component already has this practicular one
		if (ImGui::CollapsingHeader("Add Logic"))
		{
			for (SEuint i = 0; i < allLogicNames.size(); ++i)
			{
				if (std::find(exsisting->logic_class_names.begin(), exsisting->logic_class_names.end(), allLogicNames.at(i)) == exsisting->logic_class_names.end())
				{
					if (ImGui::Button(allLogicNames.at(i).c_str()))
					{
						exsisting->logic_class_names.emplace_back(allLogicNames.at(i));
						EngineGui::m_engine.GetGameLogicSystem().AssingGameLogic(exsisting->logic_class_names.back(), *exsisting);
					}
				}
			}
		}
	}
}



}//! namespace gui
}//! namespace se