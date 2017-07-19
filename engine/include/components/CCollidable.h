#ifndef SE_CCOLLIDABLE_H
#define SE_CCOLLIDABLE_H

//SE includes:
#include <components/Component.h>

namespace se
{
class CCollidable : public Component
{
public:
	///Default constructor
	CCollidable(Vec2f _aabb = Vec2f(1.0f))
		: Component(COMPONENT_TYPE::COLLIDABLE)
		, aabb(_aabb)
	{}

	///Contains axis aligned bounding boxes min and max value
	Vec2f aabb;

};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CCollidable& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_id", comp.id },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "aabb_x",comp.aabb.x },
		{ "aabb_y", comp.aabb.y },

	};
}

void inline from_json(const nlohmann::json& j, se::CCollidable& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.id = j.at("_id").get<SEint>();
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.aabb.x = j.at("aabb_x").get<SEfloat>();
	comp.aabb.y = j.at("aabb_y").get<SEfloat>();
}

}//namespace se

#endif