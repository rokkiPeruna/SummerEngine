#include <gui/EngineGui.h>
#include <core/Engine.h>

namespace se
{
namespace gui
{
EngineGui::EngineGui(priv::Engine& engine_ref)
	: m_engine(engine_ref)
{

}

EngineGui::~EngineGui()
{

}

}//namespace gui
}//namespace se