#ifndef SE_EDITOR_RENDER_H
#define SE_EDITOR_RENDER_H

//Include standard library


//Include external


//Include SE
#include <systems/TransformSystem.h>
#include <managers/ResourceManager.h>


///Brief : Editor render won't create any static objects and will draw lines even to shapes 
/// which would not othewise be drawn. 

// TODO : highlight selected

namespace se
{

namespace priv
{ 

class EditorRender
{

public:

	EditorRender();

	~EditorRender();


	EditorRender(const EditorRender&) = delete;
	void operator=(const EditorRender&) = delete;
	
	void Initialize();
	void Uninitialize();

	void Update(SEfloat deltaTime);
	void AddRenderable();
	void RemoveRenderable();


private:

	//std::vector<RenderComponent> m_rendables;
	TransformSystem* m_transform_system;

	//testing
	ShaderResource* CurrentShader;
	std::vector<SEuint> bufferObjects;

};



}// !namepsace priv

}// !namespace se



#endif // !SE_DEBUG_RENDERER_H