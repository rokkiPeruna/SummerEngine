#ifndef SE_CANIMATION_H
#define SE_CANIMATION_H

///STL includes:
#include <vector>

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
	{
		//TEST (coordinates for test_sprite_sheet.png)
		priv::AnimationFrame f1( 0, 0, 31, 36, 0.16f, 0 );

		priv::AnimationFrame f2( 46, 0, 78 - 46, 37 - 0, 0.16f,	1 );

		priv::AnimationFrame f3( 92, 0, 124 - 92, 37 - 0, 0.16f, 2 );

		priv::Animation anim1( std::vector<priv::AnimationFrame>{f1, f3, f2 } );

		animations.emplace_back(anim1);
		current_animation_index = 0;
		//TEST ENDS
	}

	SEint my_cTexture_index;		//Run-time-only value, initialized to -1. Index of the CTexture component in AnimationSystem's CTexture container
	SEint current_animation_index;	//Run-time-only value, initialized to -1.

	std::vector<priv::Animation> animations;
};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CAnimation& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data

	};
}

void inline from_json(const nlohmann::json& j, se::CAnimation& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data

}

}//namespace se

#endif