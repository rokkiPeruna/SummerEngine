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


	void AddDebugLines(const std::vector<Vec3f>& vertices, Mat4f modelMatrix);
	void AddDebugLines(const std::vector<Vec2f>& vertices, Mat4f modelMatrix);
	void AddDebugLines(Vec2f vertex, Mat4f modelMatrix);	//If only one Vec2f vertex is given, four vertices are calculated from negated and non-negated x and y

	void AddDebugPoints(const std::vector<Vec3f>& vertices, Mat4f modelMatrix);
	void AddDebugPoints(const std::vector<Vec2f>& vertices, Mat4f modelMatrix);
	void AddDebugPoints(Vec2f vertex, Mat4f modelMatrix);		//If only one Vec2f vertex is given, four vertices are calculated from negated and non-negated x and y

private:
	std::vector<Vec3f> m_dbg_verts_for_lines;		///Container holding vertices from which the debug lines are drawn
	std::vector<Vec3f> m_dbg_verts_for_points;		///Container holding vertices from which the debug points are drawn
	SEuint m_vao;									///Vertex array object handle
	ShaderResource m_debug_shader;					///Debug shader for simple primitive drawing

	SEuint _createBufferAndEnableAttrPtr(std::vector<Vec3f>& vert_data);

	void _applyUnifColor(SEuint color_location, const Vec4f& color);

	void _cleanBuffData(SEuint buffer);

	void _drawLines(SEuint count);

};

}//namespace priv
}//namespace se

#endif