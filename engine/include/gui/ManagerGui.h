#ifndef SUMMER_ENGINE_MANAGERGUI_H
#define SUMMER_ENGINE_MANAGERGUI_H


//SE includes:
#include <gui/EngineGui.h>

namespace se
{
namespace gui
{
///Brief: ManagerGui -class offers common interface for all other classes that handle SE Engine's
///managers' graphical user interface's functionality.
///It inherits some functionality from EngineGui -class
class ManagerGui : public EngineGui
{
public: 
	///Default constructor.
	///1.param: reference to Engine -class
	ManagerGui(priv::Engine& engine_ref, SEuint update_priority);
	//
	virtual ~ManagerGui() = default;
	ManagerGui(const ManagerGui&) = delete;
	void operator=(const ManagerGui&) = delete;
	ManagerGui(const ManagerGui&&) = delete;
	void operator=(const ManagerGui&&) = delete;

	virtual void Update() = 0;

};
}//namespace gui
}//namespace se

#endif