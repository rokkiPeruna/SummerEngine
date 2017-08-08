#include <core/DebugRender.h>
#include <managers/ResourceManager.h>

namespace se
{
namespace priv
{
DebugRender::DebugRender(Engine& engine_ref)
	: Render(engine_ref)
	, m_debug_verts{}
	, m_debug_indices{}
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
	//if (!m_debug_verts.size() || !m_debug_indices.size())
	//	return;
	if (!m_debug_verts.size())
	{
		m_debug_verts.emplace_back(Vec3f(0.0f, 0.0f, 0.0f));
		m_debug_verts.emplace_back(Vec3f(1.0f, 0.0f, 0.0f));
		m_debug_verts.emplace_back(Vec3f(1.0f, 1.0f, 0.0f));
	}
	if (!m_debug_indices.size())
	{
		m_debug_indices.emplace_back(0);
		m_debug_indices.emplace_back(1);
		m_debug_indices.emplace_back(2);
		m_debug_indices.emplace_back(0);
		m_debug_indices.emplace_back(2);
		m_debug_indices.emplace_back(3);
	}


	SEuint shader_handle = m_debug_shader.GetShaderID();

	glUseProgram(shader_handle);

	//Uniform locations
	SEuint view_m_loc = glGetUniformLocation(shader_handle, "view");
	SEuint persp_m_loc = glGetUniformLocation(shader_handle, "persp");

	Mat4f persp = glm::perspective(glm::radians(45.f), (SEfloat)gui::_gui_width / (SEfloat)gui::_gui_heigth, 0.1f, 100.f);
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


	glBindVertexArray(m_vao);
	SEuint pos_buffer = SEuint_max;
	glCreateBuffers(1, &pos_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, pos_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_debug_verts.at(0))*m_debug_verts.size(), m_debug_verts.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION));
	glVertexAttribPointer(static_cast<SEuint>(SHADER_ATTRIB_INDEX::POSITION), 3, GL_FLOAT, GL_FALSE, 0, 0);

	SEuint elem_buffer = SEuint_max;
	glCreateBuffers(1, &elem_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elem_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_debug_indices.at(0)) *m_debug_indices.size(), m_debug_indices.data(), GL_DYNAMIC_DRAW);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(
		GL_TRIANGLES,
		m_debug_indices.size(),
		GL_UNSIGNED_SHORT,
		0
	);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &pos_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(0);
	ClearRenderBatches();
}

void DebugRender::ClearRenderBatches()
{
	m_debug_verts.clear();
}

void DebugRender::AddDebugVertices(const std::vector<Vec3f>& vertices, Mat4f modelMatrix)
{
	for (auto v : vertices)
	{
		m_debug_verts.emplace_back(Vec3f(modelMatrix*Vec4f(v, 1.0f)));
	}
}
void DebugRender::AddDebugVertices(const std::vector<Vec2f>& vertices, Mat4f modelMatrix)
{
	for (auto v : vertices)
	{
		m_debug_verts.emplace_back(Vec3f(modelMatrix*Vec4f(v, 0.0f, 1.0f)));
	}
}

}//namespace priv
}//namespace se