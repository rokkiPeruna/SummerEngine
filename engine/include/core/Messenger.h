#ifndef SE_MESSENGER_H
#define SE_MESSENGER_H

//STL includes:
#include <vector>
#include <map>

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
	///Destructor
	~Messenger();

	///Initialize Messenger
	void Initialize();

	///Prints messages to  given log types
	void PrintMessages(SEint flags);



private:
	///Prints console messages
	void _printToConsole();
	///Prints log file messages

	///Static containers for messages
	static std::vector<Message*> m_messages;
	static std::vector<DebugMessage*> m_debugMessages;

	///Map for binding message sender to id
	std::map<SEuint64, std::string> sender_name_map;

	//ImGui checkbox booleans
	bool m_msgtype_default_checkbox;
	bool m_msgtype_info_checkbox;
	bool m_msgtype_warning_checkbox;
	bool m_msgtype_error_checkbox;
	bool m_print_debug_msgs;
};

}//namespace priv
}//namespace se
#endif