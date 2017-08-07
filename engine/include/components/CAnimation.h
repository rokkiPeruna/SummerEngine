#ifndef SE_CANIMATION_H
#define SE_CANIMATION_H

///STL includes:
#include <vector>

///SE includes:
#include <components/Component.h>

namespace se
{
struct anim_frame
{
	SEint x;
	SEint y;
	SEint width;
	SEint heigth;

	///Possible event/message sender
};

struct animation
{
	///Entity state in which the animation is played

	///Trigger for begin / end ?

	std::vector<anim_frame> frames;
};



class CAnimation : public Component
{
public:
	CAnimation():Component(COMPONENT_TYPE::ANIMATION){}

	olet tässä 

	std::vector<animation> animations;
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