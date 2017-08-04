#include <core/GameRender.h>

namespace se
{

namespace priv
{

GameRender::GameRender(std::shared_ptr<Engine> engine_ptr)
	: Render(engine_ptr)
{

}

GameRender::~GameRender()
{

}

}// !namespace priv

}// !namespace SE