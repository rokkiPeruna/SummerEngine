#ifndef SE_CANIMATION_H
#define SE_CANIMATION_H

///STL includes:
#include <vector>
#include <map>

///SE includes:
#include <components/Component.h>
#include <components/Animation.h>

namespace se
{

class CAnimation : public Component
{
public:
	CAnimation()
		: Component(COMPONENT_TYPE::ANIMATION)
		, my_cTexture_index(-1)
		, current_animation_index(-1)
		, animation_names{}
		, animations{}
	{}

	SEint my_cTexture_index;		//Run-time-only value, initialized to -1. Index of the CTexture component in AnimationSystem's CTexture container
	SEint current_animation_index;	//Run-time-only value, initialized to -1.

	std::map<std::string, SEint> animation_names;	//Has animation name as key and animation's index in animations -container as value.
	std::vector<priv::Animation> animations;		//Run-time-only variable, initialized to empty vector.
};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CAnimation& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID }
	};
	//Component specific data
	j.push_back({ "anin_names", {} });
	auto& itr = j.find("anin_names");
	for (SEint i = 0; i < comp.animations.size(); ++i)
	{
		(*itr).push_back(comp.animations.at(i).name);
	}
}

void inline from_json(const nlohmann::json& j, se::CAnimation& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.animations.clear();
	comp.animation_names.clear();

	//Check for possibly empty array
	if (j.at("anin_names").size())
	{
		std::vector<std::string> tmp = j["anin_names"];
		for (SEint i = 0; i < tmp.size(); ++i)
		{
			comp.animation_names.emplace(tmp.at(i), -1);
		}
	}
}

}//namespace se

#endif