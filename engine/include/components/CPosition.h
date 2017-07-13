#ifndef SE_CPOSITION_H
#define SE_CPOSITION_H

//SE includes:
#include <components/Component.h>

namespace se
{
class CPosition : public Component
{
public:
	///Default constructor
	CPosition(SEfloat _x = 0.0f, SEfloat _y = 0.0f, SEfloat _z = 0.0f)
		: Component(COMPONENT_TYPE::POSITION)
		, x(_x)
		, y(_y)
		, z(_z)
	{}

	///Position data as Vec2f
	SEfloat x;
	SEfloat y;
	SEfloat z;

};

//Component's serializing method. They MUST be inline functions!!! OLET TÄSSÄ
void inline to_json(nlohmann::json& j, const se::CPosition& pos)
{
	j = nlohmann::json{ {"x",pos.x}, {"y", pos.y}, {"z", pos.z} };
}

void inline from_json(const nlohmann::json& j, se::CPosition& pos)
{
	pos.x = j.at("x").get<SEfloat>();
	pos.y = j.at("y").get<SEfloat>();
	pos.z = j.at("z").get<SEfloat>();
}
}//namespace se

#endif