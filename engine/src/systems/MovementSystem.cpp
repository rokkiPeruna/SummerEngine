#include <systems/MovementSystem.h>
#include <imgui/imgui.h>

namespace se
{
namespace priv
{
MovementSystem::MovementSystem()
{

}

MovementSystem::~MovementSystem()
{

}

void MovementSystem::Initialize()
{

}

void MovementSystem::Uninitialize()
{

}

void MovementSystem::Update(float deltaTime)
{
	//Imgui test variables
	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImColor(114, 144, 154);

	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
	{
		ImGui::Begin("MovementSystem");
		SEint numOfComponents = m_cpositions.size();
		ImGui::Text("Add component");
		ImGui::SliderInt("CPosition components", &numOfComponents, 0.0f, 10.0f);
		//ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Movement editor editor")) show_test_window ^= 1;
		if (ImGui::Button("Component editor")) show_another_window ^= 1;
		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

CPosition* MovementSystem::_createCPositionComponent(CPosition& component)
{
	if (m_cpositions_map.count(component.ownerID) == 0)
	{
		m_cpositions.emplace_back(component);
		m_cpositions_map.emplace(component.ownerID, &m_cpositions.back());
		return &m_cpositions.back();
	}
	//TODO: Send message to log
	return nullptr;
}
CVelocity* MovementSystem::_createCVelocityComponent(CVelocity& component)
{
	if (m_cvelocities_map.count(component.ownerID) == 0)
	{
		m_cvelocities.emplace_back(component);
		m_cvelocities_map.emplace(component.ownerID, &m_cvelocities.back());
		return &m_cvelocities.back();
	}
	//TODO: Send message to log
	return nullptr;
}


}//namespace priv
}//namespace se