#ifndef SE_CTRANSFORMABLE_H
#define SE_CTRANSFORMABLE_H

//Include standard library

//Include external

//Include se
#include <components/Component.h>
#include <glm/gtc/matrix_transform.hpp>

namespace se
{


///Brief : Position, rotation and scale. Every object has transformable component

class CTransformable : public Component
{
public:
	///Constructor with default parameters Type : Triangle, Size : 1, Origin : 0, Rotation : 0, Scale : 1
	CTransformable(Vec3f _pos = Vec3f(0.0f), Vec3f orig = Vec3f(0.0f), SEfloat rot = 0.0f, Vec3f _scale = Vec3f(1.0f))
		: Component(COMPONENT_TYPE::TRANSFORMABLE)
		, position(_pos)
		, origin(orig)
		, rotation(rot)
		, scale(_scale)
		, points {}
	{
			
			Mat4f translationMatrix(1.0f);
			translationMatrix = glm::translate(translationMatrix, position);

			Mat4f rotationMatrix(1.0f);
			rotationMatrix = glm::rotate(rotationMatrix, rotation, Vec3f(0.0f, 0.0f, 1.0f));

			Mat4f scaleMatrix(1.0f);
			scaleMatrix = glm::scale(scaleMatrix, scale);
						
			modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
			
	};

	
	Vec3f position;
	SEfloat rotation;
	Vec3f scale;

	Vec3f origin;

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
	
}
}// !namespace se

#endif