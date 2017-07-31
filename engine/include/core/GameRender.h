#ifndef SE_GAME_RENDER_H
#define SE_GAME_RENDER_H

//Include standard library
#include <vector>

//Include external

//Include SE
#include <utility/Typedefs.h>

namespace se
{

namespace priv
{

///Brief: Game Render is not drawing any debug stuff and will divide entities in static and 
///dynamic containers

class GameRender
{
public:

	GameRender();

	~GameRender();

	GameRender(const GameRender&) = delete;
	void operator=(const GameRender&) = delete;

	void Initialize();
	void Uninitialize();

	void Update(SEfloat deltaTime);
	void AddRenderable();


private:



};

}// !namespace priv
}// !namespace se


#endif