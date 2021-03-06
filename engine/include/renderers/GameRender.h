#ifndef SUMMER_ENGINE_GAME_RENDER_H
#define SUMMER_ENGINE_GAME_RENDER_H

//Include standard library
#include <vector>

//Include external

//Include SE
#include <renderers/Render.h>

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
	//
	~GameRender() = default;
	GameRender(const GameRender&) = delete;
	void operator=(const GameRender&) = delete;
	GameRender(GameRender&&) = delete;
	void operator=(GameRender&&) = delete;

	void Initialize() override final;
	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void OnEntityAdded(const Entity& entity) override final;

	void OnEntityRemoved(const Entity&) override final;

	void ClearRenderBatches() override final;

	void OnRendableComponentChanged(const Entity&) override final;

private:

	///Render batches
	std::vector<StaticRenderBatch> m_stat_rend_batches;
	std::vector<DynamicRenderBatch> m_dyn_rend_batches;

	using batch_values = std::tuple<SEint, SEint, SEint>;

	///Map that binds render batch values to it's pointer
	std::map<batch_values, StaticRenderBatch*> m_batch_value_map_static;
	std::map<batch_values, DynamicRenderBatch*> m_batch_values_map_dynamic;

	//testing
	ShaderResource* CurrentShader;

	void _createStaticBuffers(StaticRenderBatch& staticBatch);
	void _inserValues(StaticRenderBatch& staticBatch, const Entity& entity);


};

}// !namespace priv
}// !namespace se


#endif