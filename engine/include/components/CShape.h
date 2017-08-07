#ifndef SE_CSHAPE_H
#define SE_CSHAPE_H

//Include standard library

//Include external library

//Include se
#include <components/Component.h>


namespace se
{


///Brief : CShape is basically always a circle but number of points determines how many points it has.
///with small amount of points we can have all basic shapes.

class CShape : public Component
{

public:

	CShape(SEushort num_points = 4)
		: Component(COMPONENT_TYPE::SHAPE)
		, my_Transform(-1)
	{
		SEfloat theta = 2.0f * 3.1415926f / SEfloat(num_points);
		SEfloat tangential_factor = tanf(theta);
		SEfloat radial_factor = cosf(theta);

		SEfloat x = -0.25;
		SEfloat y = -0.25;

		if (num_points < 4)
		{
			x = 0;
			y = 0.5;
		}

		for (SEushort i = 0; i < num_points; ++i)
		{
			points.emplace_back(x, y, 0.0);

			SEfloat tx = -y;
			SEfloat ty = x;

			x += tx * tangential_factor;
			y += ty * tangential_factor;

			x *= radial_factor;
			y *= radial_factor;
		}

		for (SEushort i = 0; i < num_points - 2; ++i)
		{
			indices.emplace_back(0);
			indices.emplace_back(i + 1);
			indices.emplace_back(i + 2);
		}
	};

	///Track in which transform this shape belongs to
	SEint my_Transform;

	///Actual points in 3d coordinates
	std::vector<Vec3f> points;
	
	///Indices determine which points form which triangle
	std::vector<SEushort> indices;

};

void inline to_json(nlohmann::json& j, const se::CShape& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
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

void inline from_json(const nlohmann::json& j, se::CShape& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();

	//Common spesific data

	comp.points.clear();
	std::vector<SEfloat> temp = j["points"];
	for (int i = 0; i < temp.size(); i += 3)
	{
		comp.points.emplace_back(Vec3f(temp.at(i), temp.at(i + 1), temp.at(i + 2)));
	}
}

} // !namespace se


#endif