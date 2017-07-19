#ifndef SE_CMOVABLE_H
#define SE_CMOVABLE_H

//SE includes:
#include <components/Component.h>

namespace se
{
class CMovable : public Component
{
public:
	///Default constructor
	CMovable(Vec3f pos = Vec3f(0.0f), Vec3f velo = Vec3f(0.0f), Vec3f accel = Vec3f(0.0f))
		: Component(COMPONENT_TYPE::MOVABLE)
		, position(pos)
		, velocity(velo)
		, acceleration(accel)
	{}

	Vec3f position;
	Vec3f velocity;
	Vec3f acceleration;

};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CMovable& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_id", comp.id },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "pos_x",comp.position.x },
		{ "pos_y", comp.position.y },
		{ "pos_z", comp.position.z },
		{ "velo_x",comp.velocity.x },
		{ "velo_y", comp.velocity.y },
		{ "velo_z",comp.velocity.z },
		{ "acc_x", comp.acceleration.x },
		{ "acc_y", comp.acceleration.y },
		{ "acc_z", comp.acceleration.z },

	};
}

void inline from_json(const nlohmann::json& j, se::CMovable& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.id = j.at("_id").get<SEint>();
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.position.x = j.at("pos_x").get<SEfloat>();
	comp.position.y = j.at("pos_y").get<SEfloat>();
	comp.position.z = j.at("pos_z").get<SEfloat>();
	comp.velocity.x = j.at("velo_x").get<SEfloat>();
	comp.velocity.y = j.at("velo_y").get<SEfloat>();
	comp.velocity.z = j.at("velo_z").get<SEfloat>();
	comp.acceleration.x = j.at("acc_x").get<SEfloat>();
	comp.acceleration.y = j.at("acc_y").get<SEfloat>();
	comp.acceleration.z = j.at("acc_z").get<SEfloat>();
}

}//namespace se
#endif