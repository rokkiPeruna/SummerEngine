///Brief: SE_exceptions.h contains SE engine's own exceptions to be used in parts
///of engine where try-throw-catch exception handling's overhead is not meaningful,
///etc. initializations, start-up checks, loading..
#ifndef SE_SE_EXCEPTIONS_H
#define SE_SE_EXCEPTIONS_H

//STL includes:
#include <string>
#include <exception>

namespace se
{
namespace priv
{
///Base struct for SE Engine's own exceptions. Has std::string member for holding possible message.
struct se_exception
{
	std::string msg;
	se_exception(std::string _msg) : msg(_msg) {}
};

///se_exc_json_parse_failed -exception should be thrown if nlohmann::json::parse fails.
///If used, the message should be the filepath and filename for which the parseing failed.
///This is used e.g. in JsonUtilFunctions.h 
struct se_exc_json_parse_failed : public se_exception
{
	se_exc_json_parse_failed(std::string _msg) : se_exception(_msg) {}
};

///se_exc_json_obj_faulty -exception can be used if finding json object from file or
///another json object fails. If used, the message should contain json object/file from where the search was taking place
///and name of the object failed to found.
struct se_exc_json_obj_faulty : public se_exception
{
	se_exc_json_obj_faulty(std::string _msg) : se_exception(_msg) {}
};

///se_exc_file_open_failed -exception should be thrown if std::ifstream or std::ofstream fails to open given file.
///If used, the message should be the filepath and filename which failed to open.
struct se_exc_file_open_failed : public se_exception
{
	se_exc_file_open_failed(std::string _msg) : se_exception(_msg) {}
};

}//namespace priv
}//namespace se



#endif