#ifndef SE_CANIMATION_H
#define SE_CANIMATION_H

///STL includes:
#include <vector>

///SE includes:
#include <components/Component.h>

namespace se
{
namespace priv
{
struct anim_frame
{
	SEint x;
	SEint y;
	SEint width;
	SEint heigth;
	SEfloat time;		//In seconds
	SEfloat duration;	//In seconds
	SEint ord_num;

	///Possible event/message sender
	anim_frame()
		: x(0)
		, y(0)
		, width(0)
		, heigth(0)
		, time(0)
		, duration(0)
		, ord_num(0)
	{}
	anim_frame(const anim_frame& o)
		: x(o.x)
		, y(o.y)
		, width(o.width)
		, heigth(o.heigth)
		, time(o.time)
		, duration(o.duration)
		, ord_num(o.ord_num)
	{}
};

struct animation
{
	///Way to identify?

	///Entity state in which the animation is played

	///Trigger for begin / end ?

	std::vector<anim_frame> frames;
	SEint current_frame_index;

	void Update(SEfloat deltaTime)
	{
		auto& curr_frame = frames.at(current_frame_index);
		curr_frame.time += deltaTime;
		if (curr_frame.time > curr_frame.duration)
		{
			SEint order_number = curr_frame.ord_num;
			curr_frame.time = 0;
			if (order_number == frames.size() - 1)
				current_frame_index = 0;
			else
				++current_frame_index;
		}
	}

	animation() :frames{}, current_frame_index(-1){}
	animation(const animation& o)
		: frames(o.frames)
		, current_frame_index(o.current_frame_index)
	{}
};
}//namespace priv



class CAnimation : public Component
{
public:
	CAnimation()
		: Component(COMPONENT_TYPE::ANIMATION)
		, my_cTexture_index(-1)
		, current_animation_index(-1)
	{
		//TEST (coordinates for test_sprite_sheet.png)
		priv::anim_frame f1;
		f1.x = 0;
		f1.y = 0;
		f1.width = 31;
		f1.heigth = 36;
		f1.duration = 0.16f;
		f1.ord_num = 0;

		priv::anim_frame f2;
		f2.x = 46;
		f2.y = 0;
		f2.width = 78 - 46;
		f2.heigth = 37 - 0;
		f2.duration = 0.16f;
		f2.ord_num = 1;

		priv::anim_frame f3;
		f3.x = 92;
		f3.y = 0;
		f3.width = 124 - 92;
		f3.heigth = 37 - 0;
		f3.duration = 0.16f;
		f3.ord_num = 2;

		priv::animation anim1;
		anim1.frames.emplace_back(f1);
		anim1.frames.emplace_back(f2);
		anim1.frames.emplace_back(f3);
		anim1.current_frame_index = 0;

		animations.emplace_back(anim1);
		current_animation_index = 0;
		//TEST ENDS
	}

	SEint my_cTexture_index; //Run-time-only value, initialized to -1. Index of the CTexture component in AnimationSystem's CTexture container
	SEint current_animation_index; //Run-time-only value, initialized to -1.

	std::vector<priv::animation> animations;
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

///!!!!!!!!!!!! METHODS FOR (de)serializing animations / frames


}//namespace se

#endif