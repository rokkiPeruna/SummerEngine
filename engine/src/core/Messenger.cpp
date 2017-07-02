#include <core/Messenger.h>
#include <imgui/imgui.h>
#include <core/Engine.h>

namespace se
{
namespace priv
{
std::vector<Message*> Messenger::m_messages{};
std::vector<DebugMessage*> Messenger::m_debugMessages{};

Messenger::Messenger()
{

}

Messenger::~Messenger()
{
	//Delete messages
	for (auto m : m_messages)
	{
		auto tmp = m;
		m = nullptr;
		delete tmp;
	}
	for (auto m : m_debugMessages)
	{
		auto tmp = m;
		m = nullptr;
		delete tmp;
	}
	
}

void Messenger::PrintMessages(SEint flags, SEbool printDebugAlso)
{
	ImGui::Begin("Console", &_gui_show_console_window);
	ImGui::SetWindowPos("Console", ImVec2(0.0f, 0.0f));
	ImGui::SetWindowSize(ImVec2(400, 500));


	if (flags & _messageLogType_console)
	{
		_printToConsole(printDebugAlso);
	}
	ImGui::End();
}

void Messenger::_printToConsole(SEbool printDebugAlso)
{

}

}//namespace priv
}//namespace se