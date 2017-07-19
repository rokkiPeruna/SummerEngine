#ifndef SE_RENDER_SYSTEM_H
#define SE_RENDER_SYSTEM_H

//Include standard library


//Include external


//Include SE
#include <systems/ComponentSystem.h>



namespace se
{
struct RenderableMovable
{
	SEint CMovable_index;
	SEint CTransformable_index;

	RenderableMovable(SEint cmovableIndex, SEint cTrans_index)
		: CMovable_index{ cmovableIndex },
		  CTransformable_index{ cTrans_index }
	{
	}
};

namespace priv
{

class RenderSystem : public ComponentSystem
{

public:

	RenderSystem();

	~RenderSystem();


	RenderSystem(const RenderSystem&) = delete;
	void operator=(const RenderSystem&) = delete;


	void Initialize() override final;

	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void ClearComponentContainers() override final;

	void OnEntityAdded(Entity& entity, SceneFileFormatIterator& entity_obj) override final;

	void OnEntityRemoved(Entity& entity) override final;

	SEuint CreateComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&) override final;

	void RemoveComponent(Entity&, COMPONENT_TYPE, SceneFileFormatIterator&) override final;


private:

	std::vector<Entity*> m_renderableEntities;


};



}// !namepsace priv

}// !namespace se



#endif // !SE_RENDER_SYSTEM_H