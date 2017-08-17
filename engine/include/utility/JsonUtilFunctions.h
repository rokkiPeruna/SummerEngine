#ifndef SUMMER_ENGINE_JSON_UTIL_FUNCTIONS_H
#define SUMMER_ENGINE_JSON_UTIL_FUNCTIONS_H

//STL includes:
#include <fstream>
#include <initializer_list>

//External includes:
#include <nlohmann_json/json.hpp>

//SE includes:
#include <core/Messages.h>
#include <utility/Typedefs.h>
#include <core/SE_exceptions.h>

namespace se
{
namespace util
{
///Reads file to json object. Returns boolean true if successful.
///1.param: ref to nlohmann::json object for which to write to.
///2.param: ref to filepath (MUST include filename and file suffix, e.g. path/playerdata.json)
///3.param: OPTIONAL id of the sender. See SystemAndManagerIDList.h
///--
///Throws se_exc_file_open_failed - exception if opening the file fails.
///Throws se_exc_json_parse_failed - exception if parsing fails.
inline bool ReadFileToJson(nlohmann::json& j, std::string& filepath, SEuint64 sender = _nullSysMgr_id)
{
	std::ifstream data(filepath);
	try
	{	
		if (!data.is_open())
			throw(priv::se_exc_file_open_failed("Failed to open " 
				+ filepath 
				+ " for\nreading in util::ReadFileToJson()"
				+ "\nSender: " + priv::sys_mgr_id_to_name.at(sender)));
		j = nlohmann::json::parse(data);
	}
	catch (const std::exception& exc) //Catch all std::exceptions nlohman::json::parse might throw and pass on simple se_exception appended with exc.what()
	{
		data.close();
		
		throw(priv::se_exc_json_parse_failed("Failed to parse " + filepath + " to json object [" + j.type_name() + "],\nsender: " 
			+ priv::sys_mgr_id_to_name.at(sender) 
			+ "\nnlohmann exception message: " + exc.what()));
	}
	data.close();
	return true;
}

///Rewrites file with contents of the nlohmann::json object.
///1.param: const ref to nlohmann::json object from which to read data.
///2.param: ref to filepath (MUST include filename and file suffix, e.g. path/playerdata.json)
///3.param: OPTIONAL id of the sender. See SystemAndManagerIDList.h
///--
///Sends error message if opening the file for writing fails.
inline bool RewriteFileWithJson(const nlohmann::json& j, std::string& filepath, SEuint64 sender = _nullSysMgr_id)
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