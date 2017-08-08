#ifndef SE_DEBUGRENDER_H
#define SE_DEBUGRENDER_H

///SE includes:
#include <core/Render.h>

namespace se
{
namespace priv
{
///Brief: DebugRender draws lines and forms from given vertex data for ease of modifying components
class DebugRender : public Render
{
public:
	///Default constructor.
	///1.param: pointer to Engine -class
	DebugRender(Engine& engine_ref);
	///Destructor
	~DebugRender();
	///Deleted copy ctor and assign operator
	DebugRender(const DebugRender&) = delete;
	void operator=(const DebugRender&) = delete;

	void Initialize() override final;
	void Uninitialize() override final;

	void Update(SEfloat) override final;

	void OnEntityAdded(const Entity&) override final {};
	void OnRendableComponentChanged(const Entity&) override final {}

	virtual void ClearRenderBatches();


	void AddDebugVertices(const std::vector<Vec3f>& vertices, Mat4f modelMatrix);
	void AddDebugVertices(const std::vector<Vec2f>& vertices, Mat4f modelMatrix);

private:
	std::vector<Vec3f> m_debug_verts;
	std::vector<SEushort> m_debug_indices;

	SEuint m_vao;

	ShaderResource m_debug_shader;

};

}//namespace priv
}//namespace se

#endif