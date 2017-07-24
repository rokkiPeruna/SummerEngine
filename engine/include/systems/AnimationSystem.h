#ifndef SE_ANIMATION_SYSTEM_H
#define SE_ANIMATION_SYSTEM_H

//SE includes:
#include <systems/ComponentSystem.h>
#include <components/CTexture.h>
#include <managers/ResourceManager.h>

namespace se
{
///Getter method for CTexture components
CTexture* GetTextureComponent(SEint index);

namespace priv
{
///Brief: SE_TODO: Add description
class AnimationSystem : public ComponentSystem
{
	//Friend getter method for CMovables components
	friend CTexture* se::GetTextureComponent(SEint index);

public:
	///Default constructor
	AnimationSystem();
	///Destructor
	~AnimationSystem();
	///Deleted copy constructor and assign operator
	AnimationSystem(const AnimationSystem&) = delete;
	void operator=(const AnimationSystem&) = delete;

	void Initialize() override final;

	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void ClearComponentContainers() override final;

	void OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj) override final;

	void OnEntityRemoved(Entity& e) override final;


	/*-----------------EDITOR METHODS--------------------*/

	SEuint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj) override final;

	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj) override final;

	void ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj) override final;

	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

private:
	std::vector<CTexture> m_cTextures;
	std::queue<SEint> m_free_cTexture_indices;

	///Resource manager ptr for image loading
	ResourceManager* m_res_mgr;

	///Create texture

	///Assing texture

	///OLET TÄSSÄ
	SEint remove;

};

}//Namespace priv
}//Namespace se

#endif