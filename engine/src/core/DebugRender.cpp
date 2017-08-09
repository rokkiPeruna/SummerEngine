#include <core/DebugRender.h>
#include <managers/ResourceManager.h>
#include <systems/CollisionSystem.h> //For AABB and collision polygon drawing
#include <systems/TransformSystem.h> //For shape drawing
#include <components/CTransformable.h> //For shape drawing

namespace se
{
namespace priv
{
DebugRender::DebugRender(Engine& engine_ref)
	: Render(engine_ref)
	, m_dbg_verts_for_lines{}
	, m_dbg_verts_for_points{}
	, m_model_matrices{}
	, m_dbg_verts_for_positions{}
	, m_debug_shader(SEuint_max, SEuint_max)
	, m_vao(SEuint_max)
{

}

DebugRender::~DebugRender()
{

}

void DebugRender::Initialize()
{
	m_debug_shader = *m_engine.GetResourceManager().GetShaderProgram("debug_rend");

	glGenVertexArrays(1, &m_vao);

	SEuint shader_handle = m_debug_shader.GetShaderID();
	//Binds attribs to const positions
	glBindAttribLocation(shader_handle, static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION), "vertexPosition");
	glBindAttribLocation(shader_handle, static_cast<SEuint>(SHADER_ATTRIB_INDEX::COLOR), "vertexColor");
}

void DebugRender::Uninitialize()
{

}

void DebugRender::Update(SEfloat)
{
	if (_somethingToDraw())
	{
		SEuint shader_handle = m_debug_shader.GetShaderID();
		glUseProgram(shader_handle);
		glEnable(GL_PROGRAM_POINT_SIZE);

		//Uniform locations
		SEuint view_m_loc = glGetUniformLocation(shader_handle, "view");
		SEuint persp_m_loc = glGetUniformLocation(shader_handle, "persp");
		SEuint color_loc = glGetUniformLocation(shader_handle, "line_color");

		Mat4f persp = glm::perspective(glm::radians(45.f), (SEfloat)gui::win_width / (SEfloat)gui::win_heigth, 0.1f, 100.f);
		glUniformMatrix4fv
		(
			persp_m_loc,
			1,
			GL_FALSE,
			&persp[0][0]
		);

		Mat4f view = m_engine.GetCamera()->GetCameraView();
		glUniformMatrix4fv
		(
			view_m_loc,
			1,
			GL_FALSE,
			&view[0][0]
		);

		//Init matrix container
		_initModelMatrs(gui::debug_draw_values::drawPositions);

		//Draw calls
		if (gui::debug_draw_values::drawAABBs_lines || gui::debug_draw_values::drawAABBs_points)
			_drawAABBs(color_loc, gui::debug_draw_values::drawAABBs_lines, gui::debug_draw_values::drawAABBs_points);
		if (gui::debug_draw_values::drawCollPolys_lines || gui::debug_draw_values::drawCollPolys_points)
			_drawCollPolys(color_loc, gui::debug_draw_values::drawCollPolys_lines, gui::debug_draw_values::drawCollPolys_points);
		if (gui::debug_draw_values::drawShapes_lines || gui::debug_draw_values::drawShapes_points)
			_drawShapes(color_loc, gui::debug_draw_values::drawShapes_lines, gui::debug_draw_values::drawShapes_points);
		if (gui::debug_draw_values::drawPositions)
			_drawPositions(color_loc);

		glDisable(GL_PROGRAM_POINT_SIZE); //Is this vain?
		glUseProgram(0);
		m_model_matrices.clear();
		m_dbg_verts_for_positions.clear();
	}
}

void DebugRender::ClearRenderBatches()
{
	m_dbg_verts_for_lines.clear();
	m_dbg_verts_for_points.clear();
}

void DebugRender::AddDebugLines(const std::vector<Vec3f>& vertices, Mat4f modelMatrix)
{
	for (auto& itr = vertices.begin(); itr != vertices.end(); ++itr)
	{
		auto next = ((itr + 1) != vertices.end()) ? (itr + 1) : vertices.begin();

		m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f((*itr), 1.0f)));
		m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f((*next), 1.0f)));
	}
}
void DebugRender::AddDebugLines(const std::vector<Vec2f>& vertices, Mat4f modelMatrix)
{
	for (auto& itr = vertices.begin(); itr != vertices.end(); ++itr)
	{
		auto next = ((itr + 1) != vertices.end()) ? (itr + 1) : vertices.begin();

		m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f((*itr), 0.0f, 1.0f)));
		m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f((*next), 0.0f, 1.0f)));
	}
}
void DebugRender::AddDebugLines(Vec2f vertex, Mat4f modelMatrix)
{
	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.x, vertex.x, 0.0f, 1.0f))); //First line
	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.y, vertex.x, 0.0f, 1.0f)));

	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.y, vertex.x, 0.0f, 1.0f))); //Second line
	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.y, vertex.y, 0.0f, 1.0f)));

	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.y, vertex.y, 0.0f, 1.0f))); //Third line
	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.x, vertex.y, 0.0f, 1.0f)));

	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.x, vertex.y, 0.0f, 1.0f))); //Fourth line
	m_dbg_verts_for_lines.emplace_back(Vec3f(modelMatrix * Vec4f(vertex.x, vertex.x, 0.0f, 1.0f)));
}

void DebugRender::AddDebugPoints(const std::vector<Vec3f>& vertices, Mat4f modelMatrix)
{
	for (const auto& v : vertices)
	{
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(v, 1.0f));
	}
}
void DebugRender::AddDebugPoints(const std::vector<Vec2f>& vertices, Mat4f modelMatrix)
{
	for (const auto& v : vertices)
	{
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(v, 0.0f, 1.0f));
	}
}
void DebugRender::AddDebugPoints(Vec2f vertex, Mat4f modelMatrix, SEbool not_aabb)
{
	if (!not_aabb)
	{
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(vertex.x, vertex.x, 0.0f, 1.0f)); //First point
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(vertex.y, vertex.x, 0.0f, 1.0f)); //Second point
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(vertex.y, vertex.y, 0.0f, 1.0f)); //Third point
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(vertex.x, vertex.y, 0.0f, 1.0f)); //Fourth point
	}
	else
		m_dbg_verts_for_points.emplace_back(modelMatrix * Vec4f(vertex, 0.0f, 1.0f));
}

SEbool DebugRender::_somethingToDraw()
{
	return
		gui::debug_draw_values::drawAABBs_lines |
		gui::debug_draw_values::drawAABBs_points |
		gui::debug_draw_values::drawCollPolys_lines |
		gui::debug_draw_values::drawCollPolys_points |
		gui::debug_draw_values::drawShapes_lines |
		gui::debug_draw_values::drawShapes_points |
		gui::debug_draw_values::drawPositions;
}

void DebugRender::_initModelMatrs(const SEbool fetch_positions_also)
{
	for (auto& transf_c : TransformSystem::TransformableComponents)
	{
		m_model_matrices.emplace_back(transf_c.modelMatrix);
		if (fetch_positions_also)
			m_dbg_verts_for_positions.emplace_back(transf_c.position);
	}
}

void DebugRender::_drawAABBs(SEuint color_attr_loc, const SEbool lines, const SEbool points)
{
	for (const auto& coll_c : m_engine.GetCollisionSystem().GetCCollidableContainer())
	{
		if (coll_c.ownerID == -1)
			continue;
		if (lines)
			AddDebugLines(coll_c.aabb, m_model_matrices.at(coll_c.ownerID));
		if (points)
			AddDebugPoints(coll_c.aabb, m_model_matrices.at(coll_c.ownerID));
	}
	if (lines)
	{
		SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_lines);
		_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_AABB);
		_drawLines(static_cast<SEuint>(m_dbg_verts_for_lines.size()));
		_cleanBuffData(buffer);
	}
	if (points)
	{
		SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_points);
		_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_AABB);
		_drawPoints(static_cast<SEuint>(m_dbg_verts_for_points.size()));
		_cleanBuffData(buffer);
	}

	ClearRenderBatches();
}

void DebugRender::_drawCollPolys(SEuint color_attr_loc, const SEbool lines, const SEbool points)
{
	for (const auto& coll_c : m_engine.GetCollisionSystem().GetCCollidableContainer())
	{
		if (coll_c.ownerID == -1)
			continue;
		if (lines)
			AddDebugLines(coll_c.collision_polygon, m_model_matrices.at(coll_c.ownerID));
		if (points)
			AddDebugPoints(coll_c.collision_polygon, m_model_matrices.at(coll_c.ownerID));
	}
	if (lines)
	{
		SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_lines);
		_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_CollPoly);
		_drawLines(static_cast<SEuint>(m_dbg_verts_for_lines.size()));
		_cleanBuffData(buffer);
	}
	if (points)
	{
		SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_points);
		_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_CollPoly);
		_drawPoints(static_cast<SEuint>(m_dbg_verts_for_points.size()));
		_cleanBuffData(buffer);
	}
	ClearRenderBatches();
}

void DebugRender::_drawShapes(SEuint color_attr_loc, const SEbool lines, const SEbool points)
{
	for (const auto& shape_c : m_engine.GetTransformSystem().GetCShapesContainer())
	{
		if (shape_c.ownerID == -1)
			continue;
		if (lines)
			AddDebugLines(shape_c.points, m_model_matrices.at(shape_c.ownerID));
		if (points)
			AddDebugPoints(shape_c.points, m_model_matrices.at(shape_c.ownerID));
	}
	if (lines)
	{
		SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_lines);
		_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_Shape);
		_drawLines(static_cast<SEuint>(m_dbg_verts_for_lines.size()));
		_cleanBuffData(buffer);
	}
	if (points)
	{
		SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_points);
		_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_Shape);
		_drawPoints(static_cast<SEuint>(m_dbg_verts_for_points.size()));
		_cleanBuffData(buffer);
	}
	ClearRenderBatches();
}

void DebugRender::_drawPositions(SEuint color_attr_loc)
{
	SEuint buffer = _createBufferAndEnableAttrPtr(m_dbg_verts_for_positions);
	_applyUnifColor(color_attr_loc, gui::debug_draw_values::color_pos_points);
	_drawPoints(static_cast<SEuint>(m_dbg_verts_for_positions.size()));
	_cleanBuffData(buffer);
	ClearRenderBatches();
}

SEuint DebugRender::_createBufferAndEnableAttrPtr(std::vector<Vec3f>& vert_data)
{
	glBindVertexArray(m_vao);
	SEuint buffer = SEuint_max;
	glCreateBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert_data.at(0))*vert_data.size(), vert_data.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION));
	glVertexAttribPointer(static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION), 3, GL_FLOAT, GL_FALSE, 0, 0);
	return buffer;
}

void DebugRender::_applyUnifColor(SEuint color_location, const Vec4f& color)
{
	glUniform4f(color_location, color.r, color.g, color.b, color.a);
}

void DebugRender::_cleanBuffData(SEuint buffer)
{
	glDeleteBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DebugRender::_drawLines(SEuint count)
{
	glDrawArrays(
		GL_LINES,
		0,
		count
	);
}

void DebugRender::_drawPoints(SEuint count)
{
	glDrawArrays(
		GL_POINTS,
		0,
		count
	);
}

}//namespace priv
}//namespace se