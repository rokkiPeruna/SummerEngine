#ifndef SE_ANIMATION_SYSTEM_H
#define SE_ANIMATION_SYSTEM_H

//STL includes:
#include <unordered_map>

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
	///Default constructor.
	///1.param: const ptr to Engine -class
	AnimationSystem(Engine* engine_ptr);
	///Destructor
	~AnimationSystem();
	///Deleted copy constructor and assign operator
	AnimationSystem(const AnimationSystem&) = delete;
	void operator=(const AnimationSystem&) = delete;

	void Initialize() override final;

	void Uninitialize() override final;

	void Update(SEfloat deltaTime) override final;

	void ClearComponentContainers() override final;

	void OnEntityAdded(Entity& e, Dataformat_itr& entity_obj) override final;

	void OnEntityRemoved(Entity& e) override final;

	void SetTextureResourceNames(const std::vector<std::string>& tex_names) { m_tex_res_names = { tex_names }; }

	const std::vector<std::string>& GetTextureResourceNames() { return m_tex_res_names; }

	///Returns SEuint for texture handle to be assigned to component.
	///If texture is already loaded to GPU memory, returns that handle,
	///if not, calls _createTexture() and returns handle to newly created texture
	///1.param: name of the texture with correct suffix (e.g. player.png)
	///2.param: CTexture component to which the texture is binded
	void AssignTexture(const std::string& texture_name, CTexture& tex_comp);


	SEint CreateComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	void RemoveComponent(Entity& entity, COMPONENT_TYPE component_type, Dataformat_itr& entity_obj) override final;

	Component* GetPlainComponentPtr(COMPONENT_TYPE type, SEint index_in_container) override final;

private:
	std::vector<CTexture> m_cTextures;
	std::queue<SEint> m_free_cTexture_indices;

	///Const string naming the default texture
	const std::string m_def_tex_name;

	///Container holding all texture resources' names for use in gui.
	std::vector<std::string> m_tex_res_names;

	///Resource manager ptr for image loading
	ResourceManager* m_res_mgr;

	///Unordered map holding texture ids. Key is std::string as name of the texture with suffix (e.g. tiles.png),
	///value is pair(SEuint, SEbool) containing handle to texture and boolean telling if texture has alpha channel.
	std::unordered_map<std::string, std::pair<SEuint, SEbool>> m_texture_map;

	///Create texture from pixel data.
	///1.param: Name of the texture with correct suffix (e.g. player.png).
	///--
	///Returns pair(SEuint, SEbool) containing handle (SEint) to that texture to be used by OpenGL and shaders and boolean defining if texture has alpha channel. 
	std::pair<SEuint, SEbool> _createTexture(const std::string& texture_name);
	

};

}//Namespace priv
}//Namespace se

#endif