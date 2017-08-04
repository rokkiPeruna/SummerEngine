#include <gui/CompEditorGui.h>
#include <core/Engine.h>

namespace se
{
namespace gui
{
CompEditorGui::CompEditorGui(std::shared_ptr<priv::Engine> engine_ptr)
	: EngineGui(engine_ptr)
{

}

CompEditorGui::~CompEditorGui()
{

}

}//namespace gui
}//namespace se