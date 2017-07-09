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
	: sender_name_map{}
	, m_msgtype_default_checkbox(true)
	, m_msgtype_info_checkbox(true)
	, m_msgtype_warning_checkbox(true)
	, m_msgtype_error_checkbox(true)
	, m_print_debug_msgs(true)
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

void Messenger::Initialize()
{
	//Init sender_name_map, see ids/sys_mgr_id_to_name
	sender_name_map = sys_mgr_id_to_name;
}

void Messenger::PrintMessages(SEint flags)
{
	ImGui::Begin("Console", &_gui_show_console_window);
	ImGui::SetWindowPos("Console", ImVec2(0.0f, 0.0f), ImGuiSetCond_FirstUseEver);
	ImGui::SetWindowSize(ImVec2(400, 500), ImGuiSetCond_FirstUseEver);

	if (flags & _messageLogType_console)
	{
		_printToConsole();
	}

	ImGui::End();
}

void Messenger::_printToConsole()
{
	ImGui::Checkbox("No type", &m_msgtype_default_checkbox); ImGui::SameLine();
	ImGui::Checkbox("Info", &m_msgtype_info_checkbox); ImGui::SameLine();
	ImGui::Checkbox("Warning", &m_msgtype_warning_checkbox); ImGui::SameLine();
	ImGui::Checkbox("Error", &m_msgtype_error_checkbox);
	ImGui::Checkbox("Print debug messages", &m_print_debug_msgs);

	ImVec4 textcolor;

		for (auto m : m_messages)
		{
			//Set color according to message type
			if (m_msgtype_default_checkbox && m->msgtype == MESSAGE_TYPE_INTERNAL::_NO_TYPE)
				textcolor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			else if (m_msgtype_info_checkbox && m->msgtype == MESSAGE_TYPE_INTERNAL::_INFO)
				textcolor = ImVec4(0.5f, 0.7f, 1.0f, 1.0f);
			else if (m_msgtype_warning_checkbox && m->msgtype == MESSAGE_TYPE_INTERNAL::_WARNING)
				textcolor = ImVec4(1.0f, 0.6f, 0.25f, 1.0f);
			else if (m_msgtype_error_checkbox && m->msgtype == MESSAGE_TYPE_INTERNAL::_ERROR)
				textcolor = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);

			std::string sender = "[" + sender_name_map.at(m->sndr) + "]";
			const char* message = m->msg.data();
			ImGui::TextColored(textcolor, sender.c_str());
			ImGui::TextColored(textcolor, message);
		}
#ifndef NDEBUG
	if (m_print_debug_msgs)
	{
		for (auto m : m_debugMessages)
		{
			//Set color according to message type
			if (m->msgtype == MESSAGE_TYPE_INTERNAL::_NO_TYPE)
				textcolor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			else if (m->msgtype == MESSAGE_TYPE_INTERNAL::_INFO)
				textcolor = ImVec4(0.5f, 0.7f, 1.0f, 1.0f);
			else if (m->msgtype == MESSAGE_TYPE_INTERNAL::_WARNING)
				textcolor = ImVec4(1.0f, 0.6f, 0.25f, 1.0f);
			else if (m->msgtype == MESSAGE_TYPE_INTERNAL::_ERROR)
				textcolor = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);

			std::string sender = "[DEBUG] [" + sender_name_map.at(m->sndr) + "]";
			const char* message = m->msg.data();
			ImGui::TextColored(textcolor, sender.c_str());
			ImGui::TextColored(textcolor, message);
		}
	}
#endif
}

}//namespace priv
}//namespace se