#include <gui/EngineGui.h>
#include <core/Engine.h>

namespace se
{
namespace gui
{
EngineGui::EngineGui(priv::Engine* engine_ptr)
	: m_engine(engine_ptr)
{

}

EngineGui::~EngineGui()
{

}

}//namespace gui
}//namespace se