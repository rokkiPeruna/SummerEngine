#ifndef SE_CVELOCITY_H
#define SE_CVELOCITY_H

//SE includes:
#include <components/Component.h>


namespace se
{
class CVelocity : public Component
{
public:
	///Default constructor
	CVelocity(Vec3f velocity = Vec3f(0.0f))
		: Component(COMPONENT_TYPE::VELOCITY)
		, x(velocity.x)
		, y(velocity.y)
		, z(velocity.z)
	{}

	///Three velocity components
	SEfloat x;
	SEfloat y;
	SEfloat z;
};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CVelocity& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "type", static_cast<SEint>(comp.type) },
		{ "id", comp.id },
		{ "ownerID", comp.ownerID },
		//Component specific data
		{ "velo_x",comp.x },
		{ "velo_y", comp.y },
		{ "velo_z", comp.z }
	};
}

void inline from_json(const nlohmann::json& j, se::CVelocity& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("type").get<SEint>());
	comp.id = j.at("id").get<SEint>();
	comp.ownerID = j.at("ownerID").get<SEint>();
	//Component specific data
	comp.x = j.at("velo_x").get<SEfloat>();
	comp.y = j.at("velo_y").get<SEfloat>();
	comp.z = j.at("velo_z").get<SEfloat>();
}

}//namespace se


#endif