#include <systems/AnimationSystem.h>

namespace se
{
CTexture* GetTextureComponent(SEint index)
{
	return &priv::Engine::Ptr->GetAnimationSystem().m_cTextures.at(index);
}
CAnimation* GetAnimationComponent(SEint index)
{
	return &priv::Engine::Ptr->GetAnimationSystem().m_cAnimations.at(index);
}

namespace priv
{
AnimationSystem::AnimationSystem(Engine& engine_ref)
	: ComponentSystem(engine_ref)
	, m_cTextures{}
	, m_free_cTexture_indices{}
	, m_cAnimations{}
	, m_free_cAnimation_indices{}
	, m_def_tex_name("default_texture.png")
	, m_res_mgr(nullptr)
	, m_path_to_user_files{ "faulty_path" }
	, m_texture_map{}
	, m_animation_map{}
{
	//Allocate space for m_texture_map so that we possibly avoid rehashing of keys //SE_TODO: This value should be calculated somehow from the amount of possible textures!
	m_texture_map.reserve(100);

	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TEXTURE, this);
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::ANIMATION, this);
}

void AnimationSystem::Initialize()
{
	m_event_handler.RegisterEvent(SE_Cmd_ChangeAnimation("", -1));

	m_res_mgr = &m_engine.GetResourceManager();

	//Load default texture to be used as default when new CTexture components are added
	m_texture_map.emplace(m_def_tex_name, _createTexture(m_def_tex_name));

	m_path_to_user_files = m_engine.GetRelFilePathToUserFiles();
}

void AnimationSystem::Uninitialize()
{
	m_texture_map.clear();
}

void AnimationSystem::CheckEvents()
{
	SE_Event se_event;
	while (m_event_handler.PollEvents(se_event))
	{
		switch (se_event.type)
		{
		case EventType::ChangeAnimation:
		{
			SEint entity_id = se_event.additional_data.seint;
			auto itr = std::find_if(m_cAnimations.begin(), m_cAnimations.end(), [entity_id](const CAnimation& comp) {
				if (comp.ownerID == entity_id)
					return true;
				return false;
			});
			if (itr != m_cAnimations.end())
			{
				(*itr).current_animation_index = (*itr).animation_names.at(se_event.data.char_arr);
			}

			break;
		}
		default:
			break;
		}
	}
}

void AnimationSystem::Update(SEfloat deltaTime)
{
	for (auto& c_anim : m_cAnimations)
	{
		if (c_anim.ownerID == -1 || !c_anim.animations.size())
			continue;
		assert(c_anim.my_cTexture_index != -1);

		//Update animation
		auto& current_animation = c_anim.animations.at(c_anim.current_animation_index);
		current_animation.Update(deltaTime);

		//Update texture coordinates
		auto& c_tex = m_cTextures.at(c_anim.my_cTexture_index);
		auto& current_frame = current_animation.frames.at(current_animation.current_frame_index);
		c_tex.x = current_frame.x;
		c_tex.y = current_frame.y;
		c_tex.width = current_frame.width;
		c_tex.heigth = current_frame.heigth;
	}
}

void AnimationSystem::ClearComponentContainers()
{
	m_cTextures.clear();
	m_free_cTexture_indices = {};
	m_cAnimations.clear();
	m_free_cAnimation_indices = {};
}

void AnimationSystem::OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj)
{
	SEbool has_CAnimation = false;
	if (entity.components.count(COMPONENT_TYPE::ANIMATION)) //Creation of CAnimation must be before CTexture
	{
		SEint index = _onEntityAdded_helper(entity, COMPONENT_TYPE::ANIMATION, entity_obj, m_cAnimations, m_free_cAnimation_indices);
		has_CAnimation = true;
		auto& comp = m_cAnimations.at(index);
		for (auto& a : comp.animation_names)
		{
			AssingAnimation(a.first, comp);
		}
	}
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		SEint index = _onEntityAdded_helper(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures, m_free_cTexture_indices);
		CTexture& comp = m_cTextures.at(index);
		AssignTexture(comp.name, comp);

		if (has_CAnimation)
		{
			m_cAnimations.at(entity.components.at(COMPONENT_TYPE::ANIMATION)).my_cTexture_index = index;
		}
	}
}

void AnimationSystem::OnEntityRemoved(Entity& entity)
{
	if (entity.components.count(COMPONENT_TYPE::TEXTURE))
	{
		m_free_cTexture_indices.push(entity.components.at(COMPONENT_TYPE::TEXTURE));
		m_cTextures.at(entity.components.at(COMPONENT_TYPE::TEXTURE)).ownerID = -1;
	}
	if (entity.components.count(COMPONENT_TYPE::ANIMATION))
	{
		m_free_cAnimation_indices.push(entity.components.at(COMPONENT_TYPE::ANIMATION));
		m_cAnimations.at(entity.components.at(COMPONENT_TYPE::ANIMATION)).ownerID = -1;
	}
}

SEint AnimationSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TEXTURE)
	{
		m_engine.GetCurrentRenderer()->OnRendableComponentChanged(entity);
		SEint index = _createComponent_helper<CTexture>(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures, m_free_cTexture_indices);
		AssignTexture(m_def_tex_name, m_cTextures.at(index));
		entity_obj.value().at(CompTypeAsString.at(COMPONENT_TYPE::TEXTURE)).at("tex_name") = m_def_tex_name;
		m_engine.GetCurrentRenderer()->OnEntityAdded(entity);

		//Check for possible animation component. This is done because user might add the animation component first
		if (entity.components.count(COMPONENT_TYPE::ANIMATION))
			m_cAnimations.at(entity.components.at(COMPONENT_TYPE::ANIMATION)).my_cTexture_index = index;

		return index;
	}
	else if (component_type == COMPONENT_TYPE::ANIMATION)
	{
		SEint index = _createComponent_helper<CAnimation>(entity, COMPONENT_TYPE::ANIMATION, entity_obj, m_cAnimations, m_free_cAnimation_indices);
		if (entity.components.count(COMPONENT_TYPE::TEXTURE))
			m_cAnimations.at(index).my_cTexture_index = entity.components.at(COMPONENT_TYPE::TEXTURE);
		return index;
	}
	else
	{
		MessageWarning(AnimationSys_id) << "Somehow tried to add component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return -1;
	}
}

void AnimationSystem::RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TEXTURE)
	{
		m_engine.GetCurrentRenderer()->OnRendableComponentChanged(entity);
		m_free_cTexture_indices.push(_removeComponent_helper(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures));
		m_engine.GetCurrentRenderer()->OnEntityAdded(entity);

		//If entity has animation component, invalidate it's my_cTexture_index!
		if (entity.components.count(COMPONENT_TYPE::ANIMATION))
			m_cAnimations.at(entity.components.at(COMPONENT_TYPE::ANIMATION)).my_cTexture_index = -1;
	}
	else if (component_type == COMPONENT_TYPE::ANIMATION)
	{
		m_free_cAnimation_indices.push(_removeComponent_helper(entity, COMPONENT_TYPE::ANIMATION, entity_obj, m_cAnimations));
	}
	else
	{
		MessageWarning(AnimationSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

Component* AnimationSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::TEXTURE)
	{
		return &m_cTextures.at(index_in_container);
	}
	else if (type == COMPONENT_TYPE::ANIMATION)
	{
		return &m_cAnimations.at(index_in_container);
	}
	else
		return nullptr;
}

void AnimationSystem::AssignTexture(const std::string& texture_name, CTexture& tex_comp)
{
	SETexturedata* data = nullptr;
	//Check if we have texture loaded already
	if (m_texture_map.count(texture_name))
		data = &m_texture_map.at(texture_name);
	//If not, create texture
	else
		data = &_createTexture(texture_name);

	tex_comp.handle = data->handle;
	tex_comp.has_alpha = data->alpha;
	tex_comp.parent_img_w = data->parent_i_w;
	tex_comp.parent_img_h = data->parent_i_h;
}

void AnimationSystem::AssingAnimation(const std::string& animation_name, CAnimation& anim_comp)
{
	///Check if we have that animation
	if (m_animation_map.count(animation_name))
	{
		anim_comp.animations.emplace_back(m_animation_map.at(animation_name));
		anim_comp.animation_names.at(animation_name) = static_cast<SEint>(anim_comp.animations.size() - 1);
		anim_comp.current_animation_index = 0;
	}
	else
	{
		nlohmann::json anim_obj;
		//Try read animation from json. We use try-catch block here since this function most likely will be mostly called in initializations and editor
		try
		{
			util::ReadFileToJson(anim_obj, m_path_to_user_files + "resources/animations/" + animation_name + ".json", AnimationSys_id);
		}
		catch (const se_exception&)
		{
			MessageError(AnimationSys_id) << "No animation [" + animation_name + "] found in AssingAnimation()";
			return;
		}
		std::vector<AnimationFrame> tmp_frames;
		for (auto itr = anim_obj.begin(); itr != anim_obj.end(); ++itr)
		{
			tmp_frames.emplace_back(AnimationFrame(
				static_cast<SEint>(itr.value().at("x")),
				static_cast<SEint>(itr.value().at("y")),
				static_cast<SEint>(itr.value().at("width")),
				static_cast<SEint>(itr.value().at("heigth")),
				static_cast<SEfloat>(itr.value().at("duration")),
				static_cast<SEint>(itr.value().at("ord_num"))
			));
		}
		m_animation_map.emplace(animation_name, Animation(animation_name, tmp_frames));
		anim_comp.animations.emplace_back(m_animation_map.at(animation_name));
		anim_comp.animation_names.emplace(animation_name, -1);
		anim_comp.animation_names.at(animation_name) = static_cast<SEint>(anim_comp.animations.size() - 1);
		anim_comp.current_animation_index = 0;
	}
}

SEbool AnimationSystem::AddAnimation(const std::string& anim_name, std::vector<AnimationFrame>& frames)
{
	m_animation_map.emplace(anim_name, Animation(anim_name, frames));

	return false;
}

SETexturedata& AnimationSystem::_createTexture(const std::string& texture_name)
{
	//Create pixeldata
	auto image = m_res_mgr->LoadTextureResource(texture_name);
	assert(image);

	m_texture_map.emplace(texture_name, image->data);
	return m_texture_map.at(texture_name);
}

}//namespace priv
}//namespace se