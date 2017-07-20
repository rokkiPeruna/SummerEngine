#ifndef SE_CPOSITION_H
#define SE_CPOSITION_H

//SE includes:
#include <components/Component.h>

namespace se
{
///Brief: CPosition is the smallest common nominator for entities. Every entity has to have one.
class CPosition : public Component
{
public:
	///Default constructor
	CPosition(Vec3f _pos = Vec3f(0.0f))
		: Component(COMPONENT_TYPE::POSITION)
		, x(_pos.x)
		, y(_pos.y)
		, z(_pos.z)
	{}
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
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "x", comp.x },
		{ "y", comp.y },
		{ "z", comp.z }
	};
}

void inline from_json(const nlohmann::json& j, se::CPosition& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.x = j.at("x").get<SEfloat>();
	comp.y = j.at("y").get<SEfloat>();
	comp.z = j.at("z").get<SEfloat>();
}

}//namespace se


#endif