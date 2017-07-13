#ifndef SE_CPOSITION_H
#define SE_CPOSITION_H

//SE includes:
#include <components/Component.h>

namespace se
{
class CPosition : public Component
{
public:
	///Default constructor
	CPosition(SEfloat _x = 0.0f, SEfloat _y = 0.0f, SEfloat _z = 0.0f)
		: Component(COMPONENT_TYPE::POSITION)
		, x(_x)
		, y(_y)
		, z(_z)
	{}

	///Position data as Vec2f
	SEfloat x;
	SEfloat y;
	SEfloat z;

};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CPosition& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{"type", static_cast<SEint>(comp.type)},
		{"id", comp.id},
		{"ownerID", comp.ownerID},
		//Component specific data
		{"pos_x",comp.x},
		{"pos_y", comp.y},
		{"pos_z", comp.z} 
	};
}

void inline from_json(const nlohmann::json& j, se::CPosition& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("type").get<SEint>());
	comp.id = j.at("id").get<SEint>();
	comp.ownerID = j.at("ownerID").get<SEint>();
	//Component specific data
	comp.x = j.at("pos_x").get<SEfloat>();
	comp.y = j.at("pos_y").get<SEfloat>();
	comp.z = j.at("pos_z").get<SEfloat>();
}
}//namespace se

#endif