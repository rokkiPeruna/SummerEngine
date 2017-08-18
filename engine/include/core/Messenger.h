#ifndef SUMMER_ENGINE_MESSENGER_H
#define SUMMER_ENGINE_MESSENGER_H

//STL includes:
#include <vector>
#include <map>
#include <fstream>

//SE includes:
#include <utility/Typedefs.h>

namespace se
{
struct Message;
struct DebugMessage;

enum class MESSAGE_TYPE_INTERNAL: SEint
{
	_NO_TYPE,
	_INFO,
	_WARNING,
	_ERROR
};

namespace priv
{

const SEint _messageLogType_console = 0x01;
const SEint _messageLogType_file = 0x02;

///Brief: Messenger -class handles different messages (see Messages.h) and their output.
///It has static container for messages
class Messenger
{
	friend struct se::Message;
	friend struct se::DebugMessage;
public:
	///Default constructor
	Messenger();
	~Messenger();
	Messenger(const Messenger&) = delete;
	void operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	void operator=(Messenger&&) = delete;

	///Initialize Messenger
	void Initialize();

	///Prints messages to  given log types
	void PrintMessages(SEint flags);

	///Prints all messages to file. Newest messages first. Debug messages printed after regulal messages.
	///Messages and debug messages(if defined) are separated by /*------DEBUG STARTS------*/ in file.
	///1.param: relative path to log file. Must have '/' as final chararacter.
	///2.param: filename without suffix
	///3.param: file's type (suffix: .txt, etc.)
	void CrashDumbToFile(std::string& filepath, std::string& filename, std::string& suffix);

private:
	///Prints console messages
	void _printToConsole();

	///Map for binding message sender to id
	std::map<SEuint64, std::string> sender_name_map;

	///Previous m_messages size
	SEuint m_prev_msgs_size;
	///Previous m_debugMessages size
	SEuint m_prev_dbgmsgs_size;

	///Tells if new messages have arrived
	SEbool m_newMessagesArrived;

	///Static containers for messages
	static std::vector<Message*> m_messages;
	static std::vector<DebugMessage*> m_debugMessages;


	//ImGui checkbox booleans
	SEbool m_msgtype_default_checkbox;
	SEbool m_msgtype_info_checkbox;
	SEbool m_msgtype_warning_checkbox;
	SEbool m_msgtype_error_checkbox;
	SEbool m_print_debug_msgs;
};

}//namespace priv
}//namespace se
#endif