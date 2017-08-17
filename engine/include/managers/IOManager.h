#ifndef SUMMER_ENGINE_IO_MANAGER_H
#define SUMMER_ENGINE_IO_MANAGER_H

//SE includes:
#include <managers/Manager.h>
#include <managers/IOLowLevelInputBinding.h>

namespace se
{
namespace priv
{
///Brief: IOManager -class holds and handles other input/output -classes, from low-level event classes to high-level
///user classes.. TODO: Be more precise
class IOManager : public Manager
{
public:
	///Default constructor
	///1.param: reference to Engine -class
	IOManager(Engine& engine_ref);
	//
	~IOManager() = default;
	IOManager(const IOManager&) = delete;
	void operator=(const IOManager&) = delete;
	IOManager(IOManager&&) = delete;
	void operator=(IOManager&&) = delete;

	void Initialize() override final;

	void Uninitialize() override final;

	void Update() override final;

private:


	void _handleEvents();
};


}//namespace priv
}//namespace se


#endif