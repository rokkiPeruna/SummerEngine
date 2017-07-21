#ifndef SE_CTRANSFORMABLE_H
#define SE_CTRANSFORMABLE_H

//Include standard library

//Include external

//Include se
#include <components/Component.h>
#include <glm/gtc/matrix_transform.hpp>

namespace se
{

enum BASIC_SHAPE
{
	TRIANGLE = 1,
	RECTANGLE,
	CIRCLE
};

///Brief : Position, rotation and scale. Every object has transformable component

class CTransformable : public Component
{
public:
	///Constructor with default parameters Type : Triangle, Size : 1, Origin : 0, Rotation : 0, Scale : 1
	CTransformable(Vec3f _pos = Vec3f(0.0f), BASIC_SHAPE type = BASIC_SHAPE::TRIANGLE, Vec3f orig = Vec3f(0.0f), SEfloat rot = 0.0f, Vec3f _scale = Vec3f(1.0f))
		: Component(COMPONENT_TYPE::TRANSFORMABLE)
		, position(_pos)
		, origin(orig)
		, rotation(rot)
		, scale(_scale)
		, shape_index(-1)
		, points {}
	{
		SEfloat size = 0.5;

		switch (type)
		{

		

		case BASIC_SHAPE::TRIANGLE: default:
		{

			points.emplace_back(Vec3f(0.0f, size, 0.0f));
			points.emplace_back(Vec3f(size, -size, 0.0f));
			points.emplace_back(Vec3f(-size, -size, 0.0f));

			origin = Vec3f(0.0f);
			
			Mat4f translationMatrix(1.0f);
			translationMatrix = glm::translate(translationMatrix, position);

			Mat4f rotationMatrix(1.0f);
			rotationMatrix = glm::rotate(rotationMatrix, rotation, Vec3f(0.0f, 0.0f, 1.0f));

			Mat4f scaleMatrix(1.0f);
			scaleMatrix = glm::scale(scaleMatrix, scale);
			modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			
			indices.emplace_back(0);
			indices.emplace_back(1);
			indices.emplace_back(2);
			break;
		}

		case BASIC_SHAPE::RECTANGLE:
		{
			points.emplace_back(Vec3f(-size, -size, 0.0f));
			points.emplace_back(Vec3f(size, -size, 0.0f));
			points.emplace_back(Vec3f(size, size, 0.0f));
			points.emplace_back(Vec3f(-size, size, 0.0f));
			origin = Vec3f(0.0f);
			
			Mat4f translationMatrix(
				1.0f);
			translationMatrix = glm::translate(translationMatrix, position);

			Mat4f rotationMatrix(1.0f);
			rotationMatrix = glm::rotate(rotationMatrix, rotation, Vec3f(0.0f, 0.0f, 1.0f));

			Mat4f scaleMatrix(1.0f);
			scaleMatrix = glm::scale(scaleMatrix, scale);

			modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

			indices.emplace_back(0);
			indices.emplace_back(1);
			indices.emplace_back(2);

			indices.emplace_back(2);
			indices.emplace_back(3);
			indices.emplace_back(0);


			break;
		}

		case BASIC_SHAPE::CIRCLE:
		{
			break;
		}

		}

	};

	
	Vec3f position;
	SEfloat rotation;
	Vec3f scale;

	Vec3f origin;

	SEint shape_index;

	Mat4f modelMatrix;
	std::vector<Vec3f> points;
	std::vector<SEuint> indices;

};

void inline to_json(nlohmann::json& j, const se::CTransformable& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "pos_x", comp.position.x },
		{ "pos_y", comp.position.y },
		{ "pos_z", comp.position.z },
		{ "orig_x", comp.origin.x},
		{ "orig_y", comp.origin.y},
		{ "orig_z", comp.origin.z},
		{ "rot", comp.rotation},
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
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.position.x = j.at("pos_x").get<SEfloat>();
	comp.position.y = j.at("pos_y").get<SEfloat>();
	comp.position.z = j.at("pos_z").get<SEfloat>();
	comp.origin.x = j.at("orig_x").get<SEfloat>();
	comp.origin.y = j.at("orig_y").get<SEfloat>();
	comp.origin.z = j.at("orig_z").get<SEfloat>();
	comp.rotation = j.at("rot").get<SEfloat>();
	comp.scale.x = j.at("scal_x").get<SEfloat>();
	comp.scale.y = j.at("scal_y").get<SEfloat>();
	comp.scale.z = j.at("scal_z").get<SEfloat>();

	comp.modelMatrix = glm::translate(Mat4f(1.0f), comp.position) * glm::rotate(Mat4f(1.0f), glm::radians(comp.rotation), Vec3f(0.0f, 0.0f, 1.0f)) * glm::scale(Mat4f(1.0f), comp.scale);
	
	comp.points.clear();
	std::vector<SEfloat> temp = j["points"];
	for (int i = 0; i < temp.size(); i += 3)
	{
		comp.points.emplace_back(Vec3f(temp.at(i), temp.at(i + 1), temp.at(i + 2)));
	}
}
}// !namespace se

#endif