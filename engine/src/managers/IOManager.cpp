#include <managers/IOManager.h>
#include <SDL2/include/SDL.h>


namespace se
{
namespace priv
{
IOManager::IOManager(std::shared_ptr<Engine> engine_ptr)
	: Manager(engine_ptr)
{

}

IOManager::~IOManager()
{

}

void IOManager::Initialize()
{

}

void IOManager::Uninitialize()
{

}

void IOManager::Update()
{

}

void IOManager::_handleEvents()
{
	SDL_Event event;
}

}//namespace priv
}//namespace se