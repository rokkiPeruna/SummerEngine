#include <systems/AnimationSystem.h>

namespace se
{
CTexture* GetTextureComponent(SEint index)
{
	return &priv::AnimationSystem::m_engine_ptr->GetAnimationSystem().m_cTextures.at(index);
}
CAnimation* GetAnimationComponent(SEint index)
{
	return &priv::AnimationSystem::m_engine_ptr->GetAnimationSystem().m_cAnimations.at(index);
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
	, m_tex_res_names{}
	, m_res_mgr(nullptr)
	, m_texture_map{}
{


	//Allocate space for m_texture_map so that we possibly avoid rehashing of keys //SE_TODO: This value should be calculated somehow from the amount of possible textures!
	m_texture_map.reserve(100);

	//THIS IS VERY IMPORTANT:
	//This links components to correct systems and to correct typeid! Must be done in every new system for all components it handles
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::TEXTURE, this);
	Engine::ComponentTypeToSystemPtr.emplace(COMPONENT_TYPE::ANIMATION, this);
}

AnimationSystem::~AnimationSystem()
{

}

void AnimationSystem::Initialize()
{

	m_res_mgr = &m_engine.GetResourceManager();

	//Load default texture to be used as default when new CTexture components are added
	m_texture_map.emplace(m_def_tex_name, _createTexture(m_def_tex_name));
}

void AnimationSystem::Uninitialize()
{
	m_texture_map.clear();
}

void AnimationSystem::Update(SEfloat deltaTime)
{
	for (auto& c_anim : m_cAnimations)
	{
		if (c_anim.ownerID == -1)
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
		c_tex.heigth =current_frame.heigth;
	}
}

void AnimationSystem::ClearComponentContainers()
{
	m_cTextures.clear();
	m_free_cTexture_indices = {};
}

void AnimationSystem::OnEntityAdded(Entity& entity, Dataformat_itr& entity_obj)
{
	SEbool has_CAnimation = false;
	if (entity.components.count(COMPONENT_TYPE::ANIMATION)) //Creation of CAnimation must be before CTexture
	{
		SEint index = _onEntityAdded_helper(entity, COMPONENT_TYPE::ANIMATION, entity_obj, m_cAnimations, m_free_cAnimation_indices);
		has_CAnimation = true;
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

void AnimationSystem::AssignTexture(const std::string& texture_name, CTexture& tex_comp)
{
	_texture_data* data = nullptr;
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

Component* AnimationSystem::GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container)
{
	if (type == COMPONENT_TYPE::TEXTURE)
	{
		return &m_cTextures.at(index_in_container);
	}
	else
		return nullptr;
}


AnimationSystem::_texture_data& AnimationSystem::_createTexture(const std::string& texture_name)
{
	//Create pixeldata
	auto image = m_res_mgr->LoadImageResource(texture_name);
	assert(image);

	SEint w{ image->GetData().width };
	SEint h{ image->GetData().heigth };
	assert(w > 0 && h > 0);

	_texture_data data(SEuint_max, false, w, h);

	glGenTextures(1, &data.handle);
	glBindTexture(GL_TEXTURE_2D, data.handle);

	//Check for bytes per pixel
	assert(image->GetData().bpp == 3 || image->GetData().bpp == 4);
	SEbool alpha = (image->GetData().bpp == 4) ? true : false;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	///With textures with alpha value, use GL_CLAMP_TO_EDGE to prevent borders on your texture
	///see: https:///learnopengl.com/#!Advanced-OpenGL/Blending for more information
	if (alpha)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		alpha ? GL_RGBA : GL_RGB,
		w,
		h,
		0,
		alpha ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE,
		image->GetData().pixelData.data()
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	data.alpha = alpha;

	m_texture_map.emplace(texture_name, data);
	return m_texture_map.at(texture_name);
}

}//namespace priv
}//namespace se