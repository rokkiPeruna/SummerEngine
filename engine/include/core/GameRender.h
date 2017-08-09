#ifndef SE_GAME_RENDER_H
#define SE_GAME_RENDER_H

//Include standard library
#include <vector>

//Include external

//Include SE
#include <core/Render.h>

namespace se
{

namespace priv
{

///Brief: Game Render is not drawing any debug stuff and will divide entities in static and 
///dynamic containers

class GameRender : public Render
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	GameRender(Engine& engine_ref);

	~GameRender();

	GameRender(const GameRender&) = delete;
	void operator=(const GameRender&) = delete;

	void Initialize() override final {}
	void Uninitialize()override final {}

	void Update(SEfloat) override final {}

	void OnEntityAdded(const Entity&) override final {}

	void OnEntityRemoved(const Entity& entity) override final {}

	void OnRendableComponentChanged(const Entity&) override final {}

	virtual void ClearRenderBatches() {}

};

}// !namespace priv
}// !namespace se


#endif