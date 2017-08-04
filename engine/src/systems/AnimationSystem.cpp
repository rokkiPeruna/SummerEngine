#include <systems/AnimationSystem.h>
#include <core/Engine.h>
#include <imgui/imgui.h>

namespace se
{
CTexture* GetTextureComponent(SEint index)
{
	return &priv::AnimationSystem::m_engine->GetAnimationSystem()->m_cTextures.at(index);
}

namespace priv
{
AnimationSystem::AnimationSystem(std::shared_ptr<Engine> engine_ptr)
	: ComponentSystem(engine_ptr)
	, m_cTextures{}
	, m_free_cTexture_indices{}
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
}

AnimationSystem::~AnimationSystem()
{
	m_res_mgr = nullptr;
}

void AnimationSystem::Initialize()
{
	
	m_res_mgr = m_engine->GetResourceManager();

	//Load default texture to be used as default when new CTexture components are added
	m_texture_map.emplace(m_def_tex_name, _createTexture(m_def_tex_name));
}

void AnimationSystem::Uninitialize()
{
	m_texture_map.clear();
}

void AnimationSystem::Update(SEfloat deltaTime)
{

}

void AnimationSystem::ClearComponentContainers()
{
	m_cTextures.clear();
	m_free_cTexture_indices = {};
}

void AnimationSystem::OnEntityAdded(Entity& e, Dataformat_itr& entity_obj)
{
	if (e.components.count(COMPONENT_TYPE::TEXTURE))
	{
		SEint index = _onEntityAdded_helper(e, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures, m_free_cTexture_indices);
		CTexture& comp = m_cTextures.at(index);
		AssignTexture(comp.name, comp);
	}
}

void AnimationSystem::OnEntityRemoved(Entity& e)
{
	if (e.components.count(COMPONENT_TYPE::TEXTURE))
	{
		m_free_cTexture_indices.push(e.components.at(COMPONENT_TYPE::TEXTURE));
		m_cTextures.at(e.components.at(COMPONENT_TYPE::TEXTURE)).ownerID = -1;
	}
}

SEint AnimationSystem::CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj)
{
	if (component_type == COMPONENT_TYPE::TEXTURE)
	{
		m_engine->GetCurrentRenderer()->OnRendableComponentChanged(entity);
		SEint index = _createComponent_helper<CTexture>(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures, m_free_cTexture_indices);
		AssignTexture(m_def_tex_name, m_cTextures.at(index));
		entity_obj.value().at(CompTypeAsString.at(COMPONENT_TYPE::TEXTURE)).at("tex_name") = m_def_tex_name;
		m_engine->GetCurrentRenderer()->OnEntityAdded(entity);
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
		m_engine->GetCurrentRenderer()->OnRendableComponentChanged(entity);
		m_free_cTexture_indices.push(_removeComponent_helper(entity, COMPONENT_TYPE::TEXTURE, entity_obj, m_cTextures));
		m_engine->GetCurrentRenderer()->OnEntityAdded(entity);
	}
	else
	{
		MessageWarning(AnimationSys_id) << "Somehow tried to remove component that doesn't belong to this system!!\n Check that correct system takes responsibility!!";
		return;
	}
}

void AnimationSystem::AssignTexture(const std::string& texture_name, CTexture& tex_comp)
{
	//Check if we have texture loaded already
	if (m_texture_map.count(texture_name))
	{
		tex_comp.handle = m_texture_map.at(texture_name).first;
		tex_comp.has_alpha = m_texture_map.at(texture_name).second;
	}
	//If not, create texture
	else
	{
		auto data = _createTexture(texture_name);
		tex_comp.handle = data.first;
		tex_comp.has_alpha = data.second;
	}
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


std::pair<SEuint, SEbool> AnimationSystem::_createTexture(const std::string& texture_name)
{
	//Create pixeldata
	auto image = m_res_mgr->LoadImageResource(texture_name);
	assert(image);

	SEint w{ image->GetData().width };
	SEint h{ image->GetData().heigth };
	assert(w > 0 && h > 0);

	std::pair<SEuint, SEbool> ret{ -1, false };

	glGenTextures(1, &ret.first);
	glBindTexture(GL_TEXTURE_2D, ret.first);

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
	ret.second = alpha;

	m_texture_map.emplace(texture_name, std::make_pair(ret.first, ret.second));
	return ret;
}

}//namespace priv
}//namespace se