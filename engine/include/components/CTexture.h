#ifndef SE_CTEXTURE_H
#define SE_CTEXTURE_H

//SE includes:
#include <components/Component.h>

namespace se
{
class CTexture : public Component
{
public:
	///Default constructor
	CTexture()
		: Component(COMPONENT_TYPE::TEXTURE)
		, handle(-1)
		, name("")
		, has_alpha(false)
	{}
	SEuint handle;		//Run-time only value, not saved to json. System must init this separately!
	std::string name;
	SEbool has_alpha;	//Run-time only value, not saved to json. System must init this separately!
};

//Component's serializing methods. They MUST be inline functions!!!
void inline to_json(nlohmann::json& j, const se::CTexture& comp)
{
	j = nlohmann::json
	{
		//Common component data
		{ "_type", static_cast<SEint>(comp.type) },
		{ "_ownerID", comp.ownerID },
		//Component specific data
		{ "tex_name",comp.name}
	};
}

void inline from_json(const nlohmann::json& j, se::CTexture& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.name = j.at("tex_name").get<std::string>();
}

}//namespace se
#endif