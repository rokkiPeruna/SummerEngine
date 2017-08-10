
#ifndef SE_EDITOR_RENDER_H
#define SE_EDITOR_RENDER_H


//Include SE
#include <renderers/Render.h>

///Brief : Editor render won't create any static objects and will draw lines even to shapes 
/// which would not othewise be drawn. 

// TODO : highlight selected

namespace se
{

namespace priv
{ 

class EditorRender : public Render
{

public:
	///Default constructor.
	///1.param: pointer to Engine -class
	EditorRender(Engine& engine_ref);

	~EditorRender();


	EditorRender(const EditorRender&) = delete;
	void operator=(const EditorRender&) = delete;
	
	void Initialize() override final;
	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	///Checks if there is a batch for spesific type of entities. If there is this component will be added
	///if not new one will be created
	void OnEntityAdded(const Entity& entity) override final;

	void OnEntityRemoved(const Entity& entity) override final;
	
	///Checks if the component is rendable in the first place. If it is makes sure that
	///the batch is changed
	void OnRendableComponentChanged(const Entity& entiy) override final;

	void EditorRender::ClearRenderBatches() override final;

	void AddDynRenderBatch(DynamicRenderBatch&& batch)
	{
		m_dyn_rend_batches.emplace_back(batch);
	}


private:
	///Render batches
	std::vector<DynamicRenderBatch> m_dyn_rend_batches;

	//struct cmpr_batch_values
	//{
	//	bool operator()(const batch_values& a, const batch_values& b) const
	//	{
	//		return a.x < b.x || a.y < b.y || a.z < b.z; //SE_TODO: Create better comparator
	//	}
	//};

	///Map that binds render batch values to it's pointer
	std::map<batch_values, DynamicRenderBatch*> m_batch_value_map;

	//testing
	ShaderResource* CurrentShader;

};



}// !namepsace priv

}// !namespace se



#endif // !SE_DEBUG_RENDERER_H