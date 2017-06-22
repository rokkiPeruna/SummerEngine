#ifndef SE_MESSENGER_H
#define SE_MESSENGER_H

//STL includes:
#include <cstdio>

//SE includes:
#include <utility/Typedefs.h>

namespace se
{
///Brief: Message's type
enum class MESSAGE_TYPE : SEuint
{
	INFO = 1,
	WARNING,
	ERROR
};

///Brief: Log type
enum class LOG_TYPE : SEuint
{
	DEFAULT = 0,
	CONSOLE,


};

///Brief: Messenger for sending messages to different logs
class Messenger
{
public:
	///
	//Messenger(const char* message, MESSAGE_TYPE type, );



};
}//namespace se



#endif
