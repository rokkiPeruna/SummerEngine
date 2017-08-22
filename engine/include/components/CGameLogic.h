#ifndef SUMMER_ENGINE_CGAMELOGIC_H
#define SUMMER_ENGINE_CGAMELOGIC_H

///STL includes:
#include <vector>
#include <string>

///SE includes:
#include <components/Component.h>

namespace se
{
class GameLogic;
///Brief: CGameLogic component has container which holds function pointers/lambdas/other
///that define entity behaviour in context of the game logic.
class CGameLogic : public Component
{
public:
	CGameLogic()
		: Component(COMPONENT_TYPE::GAMELOGIC)
		, logics{}
		, logic_class_names{}
		, first_act_logic_name{ "" }
		, current_gamel_index{ -1 }
	{
		logics.reserve(10);
	}

	std::vector<GameLogic*> logics; //Run-time-only value. Initialized to empty vector.
	std::vector<std::string> logic_class_names;
	std::string first_act_logic_name;
	SEint current_gamel_index;	//Run-time-only value. Initialized to -1
};


void inline to_json(nlohmann::json& j, const se::CGameLogic& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Spesific data
		{"first_act_logic", comp.first_act_logic_name }
	};

	j.push_back({ "logics", {} });
	auto& itr = j.find("logics");
	for (SEint i = 0; i < comp.logic_class_names.size(); ++i)
	{
		(*itr).push_back(comp.logic_class_names.at(i));
	}
}

void inline from_json(const nlohmann::json& j, se::CGameLogic& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();

	//Spesific data
	comp.first_act_logic_name = j.at("first_act_logic").get<std::string>();
	comp.logic_class_names.clear();
	std::vector<std::string> tmp = j.at("logics");
	for (SEint i = 0; i < tmp.size(); ++i)
	{
		comp.logic_class_names.emplace_back(tmp.at(i));
	}
}

}//namespace se

#endif