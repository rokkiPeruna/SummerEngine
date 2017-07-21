#ifndef SE_CSHAPE_H
#define SE_CSHAPE_H

//Include standard library

//Include external library

//Include se
#include <components/Component.h>


namespace se
{


class CShape : public Component
{

public:
	
	
	CShape() 
		: Component(COMPONENT_TYPE::SHAPE)
		, num_points(6)
	{
		for (int i = 0; i < num_points; ++i)
		{
			SEfloat theta = 2.0f * 3.1415926f * (float)(i) / (float)(num_points);
			SEfloat x = 1 * cosf(theta);
			SEfloat y = 1 * sinf(theta);

			points.emplace_back(x, y, 0.0f);
		}
		for (int i = 0; i < num_points; ++i)
		{
			// TODO : MAKE INDICES WORK!

		}
	};


	SEuint num_points;
	std::vector<Vec3f> points;
	std::vector<SEuint> indices;
		
private:
};


void inline to_json(nlohmann::json& j, const se::CShape& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "num_points", comp.num_points }
	};

	j.push_back({ "points",{} });
	auto& itr = j.find("points");

	for (int i = 0; i < comp.points.size(); ++i)
	{
		(*itr).push_back(comp.points.at(i).x);
		(*itr).push_back(comp.points.at(i).y);
		(*itr).push_back(comp.points.at(i).z);
	}
}

} // !namespace se


#endif