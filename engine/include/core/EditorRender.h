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
	void AddRenderable(CShape* shape, const Entity& entity);
	void RemoveRenderable();


private:

	std::vector<CShape*> m_renderables;
	

	TransformSystem* m_transform_system;

	//testing
	ShaderResource* CurrentShader;

	SEuint VAO;
	SEuint VBO;
	SEuint EBO;
	SEuint UV;

};



}// !namepsace priv

}// !namespace se



#endif // !SE_DEBUG_RENDERER_H