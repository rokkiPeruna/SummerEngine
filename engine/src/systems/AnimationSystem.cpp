#include <systems/AnimationSystem.h>
#include <core/Engine.h>

namespace se
{
CTexture* GetTextureComponent(SEint index)
{
	return &priv::Engine::Instance().GetAnimationSystem()->m_cTextures.at(index);
}

namespace priv
{
AnimationSystem::AnimationSystem()
	: m_cTextures{}
	, m_free_cTexture_indices{}
	, m_res_mgr(nullptr)
{
	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TEXTURE, this);
}

AnimationSystem::~AnimationSystem()
{
	m_res_mgr = nullptr;
}

void AnimationSystem::Initialize()
{
	m_res_mgr = Engine::Instance().GetResourceManager();
}

void AnimationSystem::Uninitialize()
{

}

void AnimationSystem::Update(SEfloat deltaTime)
{

}

void AnimationSystem::ClearComponentContainers()
{
	m_cTextures.clear();
	m_free_cTexture_indices = {};
}

void AnimationSystem::OnEntityAdded(Entity& e, SceneFileFormatIterator& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::TEXTURE))
	{
		_onEntityAdded_helper(e, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures, m_free_cTexture_indices);
	}
}

void AnimationSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::TEXTURE))
	{
		m_free_cTexture_indices.push(e.components.at(COMPONENT_TYPE::TEXTURE));
	}
}

SEuint AnimationSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TEXTURE)
	{
		return _createComponent_helper<CTexture>(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures, m_free_cTexture_indices);
	}
	else
	{
		MessageWarning(AnimationSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void AnimationSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, SceneFileFormatIterator& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TEXTURE)
	{
		m_free_cTexture_indices.push(_removeComponent_helper(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures));
	}
	else
	{
		MessageWarning(AnimationSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

void AnimationSystem::ModifyComponent(COMPONENT_TYPE type, SEint index_in_container, SceneFileFormatIterator& component_obj)
{

}

Component* AnimationSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::TEXTURE)
	{
		return &m_cTextures.at(index_in_container);
	}
	else
		return nullptr;
}

}//namespace priv
}//namespace se