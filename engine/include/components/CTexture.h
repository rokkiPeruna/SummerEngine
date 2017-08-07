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
		, name("")
		, x(0)
		, y(0)
		, width(0)
		, heigth(0)
		, parent_img_w(0)
		, parent_img_h(0)
		, handle(SEuint_max)
		, has_alpha(false)
	{}
	std::string name;	///Name of the image file with correct suffix (e.g. player.png)
	SEint x;			///Horizontal pixel position from where the texture starts. Initial value 0
	SEint y;			///Vertical pixel position from where the texture starts. Initial value 0
	SEint width;		///Value for defining texture width. Initial value is 0 which is handled as width is the same as the image width
	SEint heigth;		///Value for defining texture width. Initial value is 0 which is handled as heigth is the same as the image heigth

	SEint parent_img_w; ///Run-time only value, not saved to json. System must init this separately! -- Width of the image from which the texture is created. Initial value 0
	SEint parent_img_h; ///Run-time only value, not saved to json. System must init this separately! -- Heigth of the image from which the texture is created. Initial value 0

	SEuint handle;		///Run-time only value, not saved to json. System must init this separately! -- OpenGL texture id
	SEbool has_alpha;	///Run-time only value, not saved to json. System must init this separately! -- Indicates if image has alpha channel
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
		{ "tex_name",comp.name},
		{ "x",comp.x},
		{ "y",comp.y},
		{ "w",comp.width},
		{ "h",comp.heigth },
	};
}

void inline from_json(const nlohmann::json& j, se::CTexture& comp)
{
	//Common component data
	comp.type = static_cast<COMPONENT_TYPE>(j.at("_type").get<SEint>());
	comp.ownerID = j.at("_ownerID").get<SEint>();
	//Component specific data
	comp.name = j.at("tex_name").get<std::string>();
	comp.x = j.at("x").get<SEint>();
	comp.y = j.at("y").get<SEint>();
	comp.width = j.at("w").get<SEint>();
	comp.heigth = j.at("h").get<SEint>();
}

}//namespace se
#endif