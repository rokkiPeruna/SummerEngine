#include <gui/ManagerGui.h>

namespace se
{
namespace gui
{
ManagerGui::ManagerGui(priv::Engine& engine_ref, SEuint update_priority)
	: EngineGui(engine_ref, update_priority)
{

}

ManagerGui::~ManagerGui()
{

}

}//namespace gui
}//namespace se