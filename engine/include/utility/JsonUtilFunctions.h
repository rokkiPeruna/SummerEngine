#ifndef SE_JSON_UTIL_FUNCTIONS_H
#define SE_JSON_UTIL_FUNCTIONS_H

//STL includes:
#include <fstream>

//External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <core/Messages.h>
#include <utility/Typedefs.h>

namespace se
{
namespace util
{
bool ReadFileToJson(nlohmann::json& j, std::string& filepath, SEuint64 sender = _nullSysMgr_id)
{
	std::ifstream data(filepath);
	if (!data.is_open())
	{
		MessageError(sender) << "Failed to open " + filepath + " for\nreading in util::ReadFileToJson()";
		return false;
	}
	j = nlohmann::json::parse(data);
	data.close();
	return true;
}
bool RewriteFileWithJson(nlohmann::json& j, std::string& filepath, SEuint64 sender = _nullSysMgr_id)
{
	std::ofstream file(filepath, std::ios::trunc);
	if (!file.is_open())
	{
		MessageError(sender) << "Failed to open " + filepath + " for rewriting in util::RewriteFileWithJson()";
		return false;
	}
	file << std::setw(4) << j << std::endl;
	file.close();
	return true;
}

}//namespace priv
}//namespace se

#endif