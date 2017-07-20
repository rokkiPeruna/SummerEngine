#ifndef SE_CTRANSFORMABLE_H
#define SE_CTRANSFORMABLE_H

//Include standard library

//Include external

//Include se
#include <components/Component.h>

namespace se
{

enum BASIC_SHAPE
{
	TRIANGLE = 1,
	RECTANGLE,
	CIRCLE
};

///Brief : Transformable ia a sort of shape class with additional information considering the shape (orientation, scale and size)

class CTransformable : public Component
{
public:
	///Constructor with default parameters Type : Triangle, Size : 1, Origin : 0, Rotation : 0, Scale : 1
	CTransformable(BASIC_SHAPE type = BASIC_SHAPE::TRIANGLE, SEfloat siz = 1.0f, Vec3f orig = Vec3f(0.0f), Vec3f rot = Vec3f(0.0f, 0.0f, 0.0f), Vec3f scal = Vec3f(2.0f, 1.0f, 1.0f))
		: Component(COMPONENT_TYPE::TRANSFORMABLE)
		, size(siz)
		, origin(orig)
		, rotation(rot)
		, scale(scal)
		, points {}
	{

		Mat4f scaleMatrix = {
			scale.x, 0.0f, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f, 0.0f, scale.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		switch (type)
		{

		case BASIC_SHAPE::TRIANGLE: default:
		{
			SEfloat halfsize = size / 2.0f;
			points.emplace_back(Vec3f(-halfsize * 0.5, -halfsize, 0.0f));
			points.emplace_back(Vec3f(halfsize * 0.5, -halfsize, 0.0f));
			points.emplace_back(Vec3f(0.0f, halfsize, 0.0f));
			origin = Vec3f(0.0f);
			
			for (int i = 0; i < points.size(); ++i)
			{
				Vec4f result = Vec4f(points.at(i).x, points.at(i).y, points.at(i).z, 1.0) * scaleMatrix;
				points.at(i).x = result.x;
				points.at(i).y = result.y;
				points.at(i).z = result.z;
			}
			
			
			break;
		}

		case BASIC_SHAPE::RECTANGLE:
		{
			SEfloat halfsize = size / 2.0f;
			points.emplace_back(Vec3f(-halfsize, -halfsize, 0.0f));
			points.emplace_back(Vec3f(halfsize, -halfsize, 0.0f));
			points.emplace_back(Vec3f(halfsize, halfsize, 0.0f));
			points.emplace_back(Vec3f(-halfsize, halfsize, 0.0f));
			origin = Vec3f(0.0f);
			break;
		}

		case BASIC_SHAPE::CIRCLE:
		{


			break;
		}

		}

	};

	SEfloat size;
	Vec3f origin;
	Vec3f rotation;
	Vec3f scale;

	std::vector<Vec3f> points;
};

void inline to_json(nlohmann::json& j, const se::CTransformable& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_id", comp.id },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "size", comp.size },
		{ "orig_x", comp.origin.x},
		{ "orig_y", comp.origin.y},
		{ "orig_z", comp.origin.z},
		{ "rot_x", comp.rotation.x},
		{ "rot_y", comp.rotation.y },
		{ "rot_z", comp.rotation.z },
		{ "scal_x",comp.scale.x },
		{ "scal_y",comp.scale.y },
		{ "scal_z",comp.scale.z }
	};


	j.push_back({ "points", {} });
	auto& itr = j.find("points");

	for (int i = 0; i < comp.points.size(); ++i)
	{
		(*itr).push_back(comp.points.at(i).x);
		(*itr).push_back(comp.points.at(i).y);
		(*itr).push_back(comp.points.at(i).z);
	}

}

void inline from_json(const nlohmann::json& j, se::CTransformable& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.id = j.at("_id").get<SEint>();
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.size = j.at("size").get<SEfloat>();
	comp.origin.x = j.at("orig_x").get<SEfloat>();
	comp.origin.y = j.at("orig_y").get<SEfloat>();
	comp.origin.z = j.at("orig_z").get<SEfloat>();
	comp.rotation.x = j.at("rot_x").get<SEfloat>();
	comp.rotation.y = j.at("rot_y").get<SEfloat>();
	comp.rotation.z = j.at("rot_z").get<SEfloat>();
	comp.scale.x = j.at("scal_x").get<SEfloat>();
	comp.scale.y = j.at("scal_y").get<SEfloat>();
	comp.scale.z = j.at("scal_z").get<SEfloat>();


	// this works thought it's not so smooth.. (1 extra copy) but the data seems to be there already.
	// ask Juho about this.

	//std::vector<SEfloat> temp = j["points"];
	//for (int i = 0; i < temp.size(); i += 3)
	//{
	//	//comp.points.emplace_back(Vec3f(temp.at(i), temp.at(i + 1), temp.at(i + 2)));
	//	
	//}



//		comp.points.emplace_back(Vec3f(i, i + ));
	

	//	comp.points.emplace_back(Vec3f(
	//		
	//		j.at(index),
	//		j.at(index + 1), 
	//		j.at(index + 2)));


}



}// !namespace se

#endif