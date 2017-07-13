///Brief: Messages header and .cpp contain all that user needs
///for sending messages to log and console //TODO: Be more precise
#ifndef SE_MESSAGES_H
#define SE_MESSAGES_H

//STL includes:
#include <string>
#include <iostream>

//SE includes:
#include <utility/Typedefs.h>
#include <core/Messenger.h>
#include <ids/ComponentTypeList.h>
#include <ids/SystemAndManagerIDList.h>


namespace se
{
///Brief: Message -struct.
///Parent class to specialized messages. Shows on all builds.
///Used with operator << : Example Message(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)(see SystemAndManagerIDList.h)
struct Message
{
	void operator()(SEuint64 sender)
	{
		sndr = sender;
	}
	void operator<<(const std::string& message)
	{
		msg = message;
		priv::Messenger::m_messages.emplace_back(new Message(sndr, msgtype, msg));
	}
	SEuint64 sndr;
	MESSAGE_TYPE_INTERNAL msgtype;
	std::string msg;
	Message(SEuint64 sender, MESSAGE_TYPE_INTERNAL type = MESSAGE_TYPE_INTERNAL::_NO_TYPE, std::string message = "") : sndr(sender), msgtype(type), msg(message) {}
};



///Brief: MessageInfo is used to notify user of events that are useful to know, but which don't have much debug value.
///Used with operator << : Example MessageInfo(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct MessageInfo :public Message
{
	MessageInfo(SEuint64 sender) : Message(sender, MESSAGE_TYPE_INTERNAL::_INFO) {}
};


///Brief: MessageError is used to notify user of events that will probably crash the program.
///Used with operator << : Example MessageError(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct MessageError : public Message
{
	MessageError(SEuint64 sender) : Message(sender, MESSAGE_TYPE_INTERNAL::_ERROR) {}
};


///Brief: MessageWarning is used to notify user of events that might not crash the program, but that will have noticeable effect.
///Used with operator << : Example MessageWarning(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct MessageWarning : public Message
{
	MessageWarning(SEuint64 sender) : Message(sender, MESSAGE_TYPE_INTERNAL::_WARNING) {}
};


///In debug
#ifndef NDEBUG 
///Brief: DebugMessage -struct.
///Parent class to specialized debug messages. Shows only on debug build.
///Used with operator << : Example DebugMessage(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessage
{

	void operator()(SEuint64 sender)
	{
		sndr = sender;
	}
	void operator<<(const std::string& message)
	{
		msg = message;
		priv::Messenger::m_debugMessages.emplace_back(new DebugMessage(sndr, msgtype, msg));
	}

	SEuint64 sndr;
	MESSAGE_TYPE_INTERNAL msgtype;
	std::string msg;
	DebugMessage(SEuint64 sender, MESSAGE_TYPE_INTERNAL type = MESSAGE_TYPE_INTERNAL::_NO_TYPE, std::string message = "") : sndr(sender), msgtype(type), msg(message){}
};



///Brief: DebugMessageInfo is used to notify user of events that are useful to know, but which don't have much debug value.
///Shows on debug build only.
///Used with operator << : Example DebugMessageInfo(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessageInfo :public DebugMessage
{
	DebugMessageInfo(SEuint64 sender) : DebugMessage(sender, MESSAGE_TYPE_INTERNAL::_INFO) {}
};


///Brief: DebugMessageError is used to notify user of events that will probably crash the program.
///Shows on debug build only.
///Used with operator << : Example DebugMessageError(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessageError : public DebugMessage
{
	DebugMessageError(SEuint64 sender) : DebugMessage(sender, MESSAGE_TYPE_INTERNAL::_ERROR) {}
};


///Brief: DebugMessageWarning is used to notify user of events that might not crash the program, but that will have noticeable effect.
///Shows on debug build only.
///Used with operator << : Example DebugMessageWarning(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessageWarning : public DebugMessage
{
	DebugMessageWarning(SEuint64 sender) : DebugMessage(sender, MESSAGE_TYPE_INTERNAL::_WARNING) {}
};

///In release
#else
///Brief: DebugMessage -struct.
///Parent class to specialized debug messages. Shows only on debug build.
///Used with operator << : Example DebugMessage(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessage
{
	void operator()(SEuint64) {}
	void operator<<(const std::string&) {}
	DebugMessage(SEuint64) {}
	DebugMessage() {}
};



///Brief: DebugMessageInfo is used to notify user of events that are useful to know, but which don't have much debug value.
///Shows on debug build only.
///Used with operator << : Example DebugMessageInfo(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessageInfo :public DebugMessage
{
	DebugMessageInfo(SEuint64 sender) {}
};


///Brief: DebugMessageError is used to notify user of events that will probably crash the program.
///Shows on debug build only.
///Used with operator << : Example DebugMessageError(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessageError : public DebugMessage
{
	DebugMessageError(SEuint64 sender) {}
};


///Brief: DebugMessageWarning is used to notify user of events that might not crash the program, but that will have noticeable effect.
///Shows on debug build only.
///Used with operator << : Example DebugMessageWarning(MovementSys_id) << "This is message";
///param 1: SEuint64 sender_id (e.g. Engine_id, MovementSys_id, etc.)
struct DebugMessageWarning : public DebugMessage
{
	DebugMessageWarning(SEuint64 sender) {}
};

#endif //NDEBUG
}//namespace se
#endif