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
	CCollidable(Vec2f _aabb = Vec2f(-0.5f, 0.5f))
		: Component(COMPONENT_TYPE::COLLIDABLE)
		, aabb(_aabb)
		, collision_polygon{}
		, modelMat(1.0f)
	{
		SEfloat col_pol_offset = 0.1f;
		collision_polygon.emplace_back(_aabb.x + col_pol_offset);
		collision_polygon.emplace_back(Vec2f(_aabb.y - col_pol_offset, _aabb.x + col_pol_offset));
		collision_polygon.emplace_back(_aabb.y - col_pol_offset);
		collision_polygon.emplace_back(Vec2f(_aabb.x + col_pol_offset, _aabb.y - col_pol_offset));
	}

	///Contains axis aligned bounding boxes min and max value. Used for broad phase collision check
	Vec2f aabb;

	///Contains points for collision polygon. Used for narrow phase collision check
	std::vector<Vec2f> collision_polygon;

	///Model matrix for translating aabb and collision polygon to world coordinates
	Mat4f modelMat;		/////Run-time only value, not saved to json. System must init this separately!

};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CCollidable& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "min", comp.aabb.x },
		{ "max", comp.aabb.y },
	};
	j.push_back({ "col_pol", {} });
	auto& itr = j.find("col_pol");
	for (auto& point : comp.collision_polygon)
	{
		(*itr).push_back(point.x);
		(*itr).push_back(point.y);
	}
}

void inline from_json(const nlohmann::json& j, se::CCollidable& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.aabb.x = j.at("min").get<SEfloat>();
	comp.aabb.y = j.at("max").get<SEfloat>();

	comp.collision_polygon.clear();
	for(SEint i = 0; i < j.at("col_pol").size();)
	{
		comp.collision_polygon.emplace_back(Vec2f(
			static_cast<SEfloat>(j.at("col_pol").at(i)), static_cast<SEfloat>(j.at("col_pol").at(i+1))
		));
		i += 2;
	}
}

}//namespace se

#endif