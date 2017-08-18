#ifndef SUMMER_ENGINE_CDYNAMIC_H
#define SUMMER_ENGINE_CDYNAMIC_H

//SE includes:
#include <components/Component.h>

namespace se
{
class CDynamic : public Component
{
public:
	///Default constructor
	CDynamic(Vec3f velo = Vec3f(0.0f), Vec3f accel = Vec3f(0.0f))
		: Component(COMPONENT_TYPE::DYNAMIC)
		, velocity(velo)
		, acceleration(accel)
	{}
	Vec3f velocity;
	Vec3f acceleration;
};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CDynamic& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "velo_x",comp.velocity.x },
		{ "velo_y", comp.velocity.y },
		{ "velo_z",comp.velocity.z },
		{ "acc_x", comp.acceleration.x },
		{ "acc_y", comp.acceleration.y },
		{ "acc_z", comp.acceleration.z }
	};
}

void inline from_json(const nlohmann::json& j, se::CDynamic& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.velocity.x = j.at("velo_x").get<SEfloat>();
	comp.velocity.y = j.at("velo_y").get<SEfloat>();
	comp.velocity.z = j.at("velo_z").get<SEfloat>();
	comp.acceleration.x = j.at("acc_x").get<SEfloat>();
	comp.acceleration.y = j.at("acc_y").get<SEfloat>();
	comp.acceleration.z = j.at("acc_z").get<SEfloat>();
}

}//namespace se
#endif