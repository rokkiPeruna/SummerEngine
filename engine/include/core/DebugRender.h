#ifndef SE_DEBUGRENDER_H
#define SE_DEBUGRENDER_H

///

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
	void AddDebugLines(Vec2f vertex, Mat4f modelMatrix);	//If only one Vec2f vertex is given, four vertices are calculated from negated and non-negated x and y (Assumed use for AABB)

	void AddDebugPoints(const std::vector<Vec3f>& vertices, Mat4f modelMatrix);
	void AddDebugPoints(const std::vector<Vec2f>& vertices, Mat4f modelMatrix);
	void AddDebugPoints(Vec2f vertex, Mat4f modelMatrix, SEbool not_aabb = false);	//If only one Vec2f vertex is given and not_aabb is false, four vertices are calculated from negated and non-negated x and y (Assumed use for AABB)

private:
	std::vector<Vec3f> m_dbg_verts_for_lines;		///Container holding vertices from which the debug lines are drawn
	std::vector<Vec3f> m_dbg_verts_for_points;		///Container holding vertices from which the debug points are drawn
	std::vector<Mat4f> m_model_matrices;			///Container holding model matrices for each frame.
	std::vector<Vec3f> m_dbg_verts_for_positions;	///Container holding entities positions
	SEuint m_vao;									///Vertex array object handle
	ShaderResource m_debug_shader;					///Debug shader for simple primitive drawing

	SEbool _somethingToDraw();

	void _initModelMatrs(const SEbool fetch_positions_also); ///Inits also m_dbg_verts_for_positions if boolean is true


	void _drawAABBs(SEuint color_attr_loc, const SEbool lines, const SEbool points);

	void _drawCollPolys(SEuint color_attr_loc, const SEbool lines, const SEbool points);

	void _drawShapes(SEuint color_attr_loc, const SEbool lines, const SEbool points);

	void _drawPositions(SEuint color_attr_loc);


	SEuint _createBufferAndEnableAttrPtr(std::vector<Vec3f>& vert_data);

	void _applyUnifColor(SEuint color_location, const Vec4f& color);

	void _cleanBuffData(SEuint buffer);

	void _drawLines(SEuint count);

	void _drawPoints(SEuint count);

};

}//namespace priv
}//namespace se

#endif